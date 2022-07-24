// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/bootup.h"

namespace sysinfo {
namespace computer {

TEST(BootupTest, TestGetBootup) {
  BootupList list;
  const bool ok = getBootup(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 1);
  ASSERT_TRUE(list.at(0).start_time.isValid());
  ASSERT_LT(list.at(0).start_time, QDateTime::currentDateTime());
}

}  // namespace computer
}  // namespace sysinfo