// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/devices.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const DeviceInfo& info) {
  QJsonObject obj;
  obj.insert("batteries", dump(info.batteries));
  obj.insert("dmi", dump(info.dmi));
  obj.insert("inputDevices", dump(info.input_list));
  obj.insert("memory", dump(info.memory_info));
  obj.insert("pciDevices", dump(info.pci_list));
  obj.insert("usbDevices", dump(info.usb_list));
  return obj;
}

}  // namespace devices
}  // namespace sysinfo