// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/devices.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const DevicesInfo& info) {
  QJsonObject obj;
  obj.insert(kNameAudioDevices, QJsonArray::fromStringList(info.audio_devices));
  obj.insert(kNameBatteries, dump(info.batteries));
  obj.insert(kNameDmi, dump(info.dmi));
  obj.insert(kNameInputDevices, dump(info.input_list));
  obj.insert(kNameMemory, dump(info.memory_info));
  obj.insert(kNamePciDevices, dump(info.pci_list));
  obj.insert(kNameProcessors, dump(info.processors));
  obj.insert(kNameSensors, dump(info.sensors));
  obj.insert(kNameStorageDevices, dump(info.storage_list));
  obj.insert(kNameUsbDevices, dump(info.usb_list));
  return obj;
}

}  // namespace devices
}  // namespace sysinfo