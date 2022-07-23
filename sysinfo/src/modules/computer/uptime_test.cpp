// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/uptime.h"

namespace sysinfo {
namespace computer {

TEST(UptimeTest, TestGetUptime) {
  UptimeInfo info{};
  const bool ok = getUptime(info);
  ASSERT_TRUE(ok);
  ASSERT_GT(info.minutes + info.hours + info.days, 0);
}

}  // namespace computer
}  // namespace sysinfo