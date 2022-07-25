// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/usb.h"

namespace sysinfo {
namespace devices {

TEST(UsbTest, TestGetUserDevices) {
  UsbDevList list;
  const bool ok = getUsbDevices(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 3);
}

}  // namespace devices
}  // namespace sysinfo