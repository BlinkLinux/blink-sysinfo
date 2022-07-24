// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/group.h"

namespace sysinfo {
namespace computer {

TEST(GroupTest, TestGetGroupList) {
  GroupList list;
  const bool ok = getGroupList(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 5);
  ASSERT_EQ(list.first().gid, 0);
  ASSERT_EQ(list.first().members, QStringList("root"));
}

}  // namespace computer
}  // namespace sysinfo