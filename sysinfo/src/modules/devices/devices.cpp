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
#include "modules/devices/processor.h"
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
  ok &= getProcessorList(info.processors);
  ok &= getSensorList(info.sensors);
  ok &= getStorageList(info.storage_list);
  ok &= getUsbDevices(info.usb_list);
  return ok;
}

bool getSpecificSection(const QString& name, QJsonObject& root) {
  QJsonObject devices;
  if (root.contains(kNameDevices)) {
    devices = root.value(kNameDevices).toObject();
  }

  if (name == kNameAudioDevices) {
    AudioDevices audio_devices;
    getAudioDevices(audio_devices);
    devices.insert(kNameAudioDevices, QJsonArray::fromStringList(audio_devices));
  } else if (name == kNameBatteries) {
    BatteryList list;
    getBatteryInfo(list);
    devices.insert(kNameBatteries, dump(list));
  } else if (name == kNameDmi) {
    Dmi dmi;
    getDmiInfo(dmi);
    devices.insert(kNameDmi, dump(dmi));
  } else if (name == kNameInputDevices) {
    InputDevList list;
    getInputDevices(list);
    devices.insert(kNameInputDevices, dump(list));
  } else if (name == kNameMemory) {
    MemoryInfos list;
    getMemoryInfo(list);
    devices.insert(kNameMemory, dump(list));
  } else if (name == kNamePciDevices) {
    PciDevList list;
    getPciDevList(list);
    devices.insert(kNamePciDevices, dump(list));
  } else if (name == kNameProcessors) {
    Processors list;
    getProcessorList(list);
    devices.insert(kNameProcessors, dump(list));
  } else if (name == kNameSensors) {
    Sensors sensors;
    getSensorList(sensors);
    devices.insert(kNameSensors, dump(sensors));
  } else if (name == kNameStorageDevices) {
    StorageList list;
    getStorageList(list);
    devices.insert(kNameStorageDevices, dump(list));
  } else if (name == kNameUsbDevices) {
    UsbDevList list;
    getUsbDevices(list);
    devices.insert(kNameUsbDevices, dump(list));
  } else {
    qWarning() << "Unknown section:" << name;
    return false;
  }

  root.insert(kNameDevices, devices);

  return true;
}

}  // namespace devices
}  // namespace sysinfo