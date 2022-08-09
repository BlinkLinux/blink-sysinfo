// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/display.h"

namespace sysinfo {
namespace computer {

TEST(DisplayTest, TestGetGlxInfo) {
  OpenGlInfo info{};
  const bool ok = getGlxInfo(info);
  ASSERT_TRUE(ok);
  ASSERT_TRUE(info.direct_rendering);
  ASSERT_TRUE(info.version.contains("Mesa"));
}

TEST(DisplayTest, TestGetX11Info) {
  Display display{};
  const bool ok = getX11Info(display);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(display.monitors.isEmpty());
  ASSERT_FALSE(display.x11_extensions.isEmpty());
}

}  // namespace computer
}  // namespace sysinfo