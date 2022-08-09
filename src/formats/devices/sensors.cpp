// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/sensors.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const Sensor& sensor) {
  QJsonObject obj;
  obj.insert("name", sensor.name);
  obj.insert("driver", sensor.driver_path);
  obj.insert("monName", sensor.mon_name);
  obj.insert("friendlyName", sensor.friendly_name);
  obj.insert("unit", sensor.unit);
  obj.insert("value", sensor.value);
  return obj;
}

QJsonArray dump(const Sensors& list) {
  QJsonArray array;
  for (const auto& sensor : list) {
    array.append(dump(sensor));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo