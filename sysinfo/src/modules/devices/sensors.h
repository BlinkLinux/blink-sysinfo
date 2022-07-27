// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_SENSORS_H_
#define SYSINFO_SRC_MODULES_DEVICES_SENSORS_H_

#include <QMap>

#include "formats/devices/sensors.h"

namespace sysinfo {
namespace devices {

bool getSensorList(Sensors& list);

bool readSensorsHwmon(Sensors& list);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_DEVICES_SENSORS_H_
