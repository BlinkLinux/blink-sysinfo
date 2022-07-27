// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/devices.h"

#include "modules/devices/audio_devices.h"
#include "modules/devices/battery.h"
#include "modules/devices/dmi.h"
#include "modules/devices/input_devices.h"
#include "modules/devices/memory.h"
#include "modules/devices/pci.h"
#include "modules/devices/sensors.h"
#include "modules/devices/storage.h"
#include "modules/devices/usb.h"

namespace sysinfo {
namespace devices {

bool getDevicesInfo(DevicesInfo& info) {
  bool ok = true;
  ok &= getAudioDevices(info.audio_devices);
  ok &= getBatteryInfo(info.batteries);
  ok &= getDmiInfo(info.dmi);
  ok &= getInputDevices(info.input_list);
  ok &= getMemoryInfo(info.memory_info);
  ok &= getPciDevList(info.pci_list);
  ok &= getSensorList(info.sensors);
  ok &= getStorageList(info.storage_list);
  ok &= getUsbDevices(info.usb_list);
  return ok;
}

}  // namespace devices
}  // namespace sysinfo