// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/input_devices.h"

namespace sysinfo {
namespace devices {

TEST(InputDevTest, TestGetInputDevList) {
  InputDevList list;
  const bool ok = getInputDevices(list);
  ASSERT_TRUE(ok);
  ASSERT_GE(list.length(), 3);
}

}  // namespace devices
}  // namespace sysinfo