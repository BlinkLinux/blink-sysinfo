// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/pci.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

#include "base/process.h"
#include "base/unit.h"
#include "modules/shared/vendor.h"

namespace sysinfo {
namespace devices {

bool getPciDevList(PciDevList& list) {
  QString out;
  if (!getCommandOutput("lspci -v", out)) {
    return false;
  }

  QRegularExpression id_pattern(R"(([\d:.]+)\s([^:]+):\s(.*))");
  QRegularExpression mem_pattern("Memory at ([^ ]+).+\\[size=([^\\]]+)");
  QRegularExpression io_ports_pattern("I/O ports at ([^ ]+).+\\[size=([^\\]]+)");
  QRegularExpression flags_pattern("IRQ (\\d+)");
  QString line;
  QTextStream stream(&out);
  PciDev dev{};
  while (stream.readLineInto(&line)) {
    if (line.isEmpty()) {
      // End of device.
      list.append(dev);
      dev = PciDev{};
      continue;
    }

    if (!line.startsWith('\t')) {
      // First line.
      const auto match = id_pattern.match(line);
      if (match.isValid()) {
        dev.id = match.captured(1);
        dev.dev_class = match.captured(2);
        dev.name = match.captured(3);
        dev.vendor_name = getVendorName(dev.name);
        dev.vendor_url = getVendorUrl(dev.name);
      }
      continue;
    }

    line = line.trimmed();
    if (line.startsWith("Subsystem:")) {
      dev.subsystem = line.mid(static_cast<int>(strlen("Subsystem:"))).trimmed();
      dev.oem_vendor_name = getVendorName(dev.subsystem);
      dev.oem_vendor_url = getVendorUrl(dev.subsystem);
    } else if (line.startsWith("Flags:")) {
      dev.is_bus_master = line.contains("bus master");
      const auto match = flags_pattern.match(line);
      if (match.isValid()) {
        dev.irq = match.captured(1).toInt();
      }
    } else if (line.startsWith("I/O ports")) {
      const auto match = io_ports_pattern.match(line);
      if (match.isValid()) {
        dev.io_ports.start = match.captured(1).toLong(nullptr, 16);
        dev.io_ports.size = parseMemSize(match.captured(2));
      }
    } else if (line.startsWith("Memory at")) {
      PciDevMemory memory{};
      memory.is_64_bits = line.contains("64-bit");
      memory.is_prefetchable = !line.contains("non-prefetchable");
      const auto match = mem_pattern.match(line);
      if (match.isValid()) {
        memory.start = match.captured(1).toLongLong(nullptr, 16);
        memory.size = parseMemSize(match.captured(2));
      }
    } else if (line.startsWith("Kernel driver in use:")) {
      const QString module = line.mid(static_cast<int>(strlen("Kernel driver in use:")));
      dev.kernel_modules.append(module);
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo