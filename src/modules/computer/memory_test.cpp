// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/memory.h"

namespace sysinfo {
namespace computer {

TEST(MemoryTest, TestGetMemoryInfo) {
  Memory memory{};
  const bool ok = getMemoryInfo(memory);
  ASSERT_TRUE(ok);
  ASSERT_GT(memory.total, 1000);
}

}  // namespace computer
}  // namespace sysinfo