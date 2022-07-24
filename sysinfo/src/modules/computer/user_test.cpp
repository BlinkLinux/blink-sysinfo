// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/user.h"

namespace sysinfo {
namespace computer {

TEST(UserTest, TestGetUserList) {
  UserList list;
  const bool ok = getUserList(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 5);
  ASSERT_EQ(list.first().uid, 0);
}

}  // namespace computer
}  // namespace sysinfo