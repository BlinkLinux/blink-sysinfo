// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/battery.h"

namespace sysinfo {
namespace devices {

TEST(BatteryTest, TestScanBatteryItemSysfs) {
  Battery battery;
  const bool ok = scanBatteryItemSysfs("/sys/class/power_supply/BAT0", battery);
  ASSERT_TRUE(ok);
}

}  // namespace devices
}  // namespace sysinfo