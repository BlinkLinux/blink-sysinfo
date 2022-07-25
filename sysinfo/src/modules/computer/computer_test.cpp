// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/computer.h"

namespace sysinfo {
namespace computer {

TEST(ComputerTest, TestGetComputerInfo) {
  ComputerInfo info;
  const bool ok = getComputerInfo(info);
  ASSERT_TRUE(ok);
}

}  // namespace computer
}  // namespace sysinfo