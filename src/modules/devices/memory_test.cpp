// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/memory.h"

namespace sysinfo {
namespace devices {

TEST(MemoryTest, TestGetMemoryInfo) {
  MemoryInfos map;
  const bool ok = getMemoryInfo(map);
  ASSERT_TRUE(ok);
  ASSERT_TRUE(map.contains("MemTotal"));
  ASSERT_TRUE(map.contains("Active"));
}

}  // namespace devices
}  // namespace sysinfo