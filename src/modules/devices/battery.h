// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_BATTERY_H_
#define SYSINFO_SRC_MODULES_DEVICES_BATTERY_H_

#include "formats/devices/battery.h"

namespace sysinfo {
namespace devices {

bool getBatteryInfo(BatteryList& list);

bool scanBatterySysfs(BatteryList& list);
bool scanBatteryItemSysfs(const QString& dir_name, Battery& battery);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_DEVICES_BATTERY_H_
