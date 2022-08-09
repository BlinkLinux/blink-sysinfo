// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/sensors.h"

namespace sysinfo {
namespace devices {

TEST(SensorsTest, TestGetSensors) {
  Sensors list;
  const bool ok = getSensorList(list);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(list.isEmpty());
}

TEST(SensorsTest, TestReadSensorsHwmon) {
  Sensors list;
  const bool ok = readSensorsHwmon(list);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(list.isEmpty());
}

}  // namespace devices
}  // namespace sysinfo