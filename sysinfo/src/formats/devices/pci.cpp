// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/pci.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const PciDevMemory& memory) {
  QJsonObject obj;
  obj.insert("start", memory.start);
  obj.insert("size", memory.size);
  obj.insert("is64Bits", memory.is_64_bits);
  obj.insert("isPrefetchable", memory.is_prefetchable);
  return obj;
}

QJsonObject dump(const PciDevIoPorts& io_port) {
  QJsonObject obj;
  obj.insert("start", io_port.start);
  obj.insert("size", io_port.size);
  return obj;
}

QJsonObject dump(const PciDev& dev) {
  QJsonObject obj;
  obj.insert("id", dev.id);
  obj.insert("class", dev.dev_class);
  obj.insert("name", dev.name);
  obj.insert("subsystem", dev.subsystem);

  obj.insert("vendorName", dev.vendor_name);
  obj.insert("vendorUrl", dev.vendor_url);
  obj.insert("oemVendorName", dev.oem_vendor_name);
  obj.insert("oemVendorUrl", dev.oem_vendor_url);

  obj.insert("ioPorts", dump(dev.io_ports));
  obj.insert("kernelModules", QJsonArray::fromStringList(dev.kernel_modules));
  QJsonArray memories;
  for (const auto& memory : dev.memories) {
    memories.append(dump(memory));
  }
  obj.insert("memories", memories);

  obj.insert("irq", dev.irq);
  obj.insert("isBusMaster", dev.is_bus_master);

  return obj;
}

QJsonArray dump(const PciDevList& list) {
  QJsonArray array;
  for (const auto& dev : list) {
    array.append(dump(dev));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo