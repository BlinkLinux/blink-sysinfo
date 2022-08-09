// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/development.h"

namespace sysinfo {
namespace computer {

TEST(DevelopmentTest, TestGetDevelopment) {
  Development dev;
  const bool ok = getDevelopmentEnv(dev);
  ASSERT_TRUE(ok);
  ASSERT_GT(dev.scripting.length(), 6);
}

}  // namespace computer
}  // namespace sysinfo