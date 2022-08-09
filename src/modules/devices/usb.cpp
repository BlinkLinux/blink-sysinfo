// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/usb.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

#include "base/process.h"

namespace sysinfo {
namespace devices {

bool getUsbDevices(UsbDevList& list) {
  return scanUsbLsusb(list);
}

bool scanUsbLsusb(UsbDevList& list) {
  QString out;
  if (!getCommandOutput("lsusb", out)) {
    return false;
  }

  QRegularExpression id_pattern("Bus (\\d+) Device (\\d+)");
  QTextStream stream(&out);
  QString line;
  bool ok = true;

  while (stream.readLineInto(&line)) {
    const auto match = id_pattern.match(line);
    if (!match.isValid()) {
      continue;
    }

    UsbDev dev{};
    dev.bus_id = match.captured(1);
    dev.device_id = match.captured(2);
    dev.id = QString("%1:%2").arg(dev.bus_id, dev.device_id);
    ok &= scanUsbLsusb(dev);
    list.append(dev);
  }

  return ok;
}

bool scanUsbLsusb(UsbDev& dev) {
  QString out;
  if (!getCommandOutputWithArgs("lsusb", {"-v", "-s", dev.id}, out)) {
    return false;
  }

  QRegularExpression id_pattern(".+([0-9a-fx]+)\\s+([^\\s]+)");
  QTextStream stream(&out);
  QString line;
  while (stream.readLineInto(&line)) {
    if (line.contains("bcdUSB")) {
      dev.usb_version = line.remove("bcdUSB").trimmed();
    } else if (line.contains("idVendor")) {
      const auto match = id_pattern.match(line);
      if (match.isValid()) {
        dev.id_vendor = match.captured(1);
        dev.id_vendor_name = match.captured(2);
      }
    } else if (line.contains("idProduct")) {
      const auto match = id_pattern.match(line);
      if (match.isValid()) {
        dev.id_product = match.captured(1);
        dev.id_product_name = match.captured(2);
      }
    } else if (line.contains("isSerial")) {
      dev.is_serial = !line.contains("0");
    } else if (line.contains("MaxPower")) {
      dev.max_power = line.remove("MaxPower").trimmed();
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo