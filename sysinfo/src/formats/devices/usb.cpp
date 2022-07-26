// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/usb.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const UsbDev& dev) {
  QJsonObject obj;
  obj.insert("id", dev.id);
  obj.insert("busId", dev.bus_id);
  obj.insert("deviceId", dev.device_id);
  obj.insert("name", dev.name);
  obj.insert("usbVersion", dev.usb_version);
  obj.insert("vendor", dev.id_vendor);
  obj.insert("vendorName", dev.id_vendor_name);
  obj.insert("product", dev.id_product);
  obj.insert("productName", dev.id_product_name);
  obj.insert("manufacturer", dev.id_manufacturer);
  obj.insert("maxPower", dev.max_power);
  obj.insert("isSerial", dev.is_serial);
  return obj;
}

QJsonArray dump(const UsbDevList& list) {
  QJsonArray array;
  for (const auto& dev : list) {
    array.append(dump(dev));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo