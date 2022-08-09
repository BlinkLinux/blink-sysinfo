// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "base/unit.h"

namespace sysinfo {

TEST(UnitTest, TestParseMemSize) {
  ASSERT_EQ(parseMemSize("16"), 16);
  ASSERT_EQ(parseMemSize("16 \t\n"), 16);
  ASSERT_EQ(parseMemSize("4k"), 4096);
  ASSERT_EQ(parseMemSize("4 k"), 4096);
  ASSERT_EQ(parseMemSize("4M"), 4194304);
  ASSERT_EQ(parseMemSize(" 4 M"), 4194304);
}

}  // namespace sysinfo