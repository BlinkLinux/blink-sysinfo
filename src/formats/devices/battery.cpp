// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/battery.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const Battery& battery) {
  QJsonObject obj;
  obj.insert("status", battery.status);
  obj.insert("capacity", battery.capacity);
  obj.insert("capacityLevel", battery.capacity_level);
  obj.insert("technology", battery.technology);
  obj.insert("manufacturer", battery.manufacturer);
  obj.insert("modelName", battery.model_name);
  obj.insert("serialNumber", battery.serial_number);
  return obj;
}

QJsonArray dump(const BatteryList& list) {
  QJsonArray array;
  for (const auto& battery : list) {
    array.append(dump(battery));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo