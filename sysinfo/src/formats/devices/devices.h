// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_DEVICES_H_
#define SYSINFO_SRC_FORMATS_DEVICES_DEVICES_H_

#include <QJsonObject>

#include "formats/devices/audio_devices.h"
#include "formats/devices/battery.h"
#include "formats/devices/dmi.h"
#include "formats/devices/input_devices.h"
#include "formats/devices/memory.h"
#include "formats/devices/pci.h"
#include "formats/devices/sensors.h"
#include "formats/devices/usb.h"

namespace sysinfo {
namespace devices {

struct DevicesInfo {
  AudioDevices audio_devices{};
  BatteryList batteries{};
  Dmi dmi{};
  InputDevList input_list{};
  MemoryInfos memory_info{};
  PciDevList pci_list{};
  Sensors sensors{};
  UsbDevList usb_list{};
};

QJsonObject dump(const DevicesInfo& info);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_DEVICES_H_
