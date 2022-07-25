// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/network/routing_table.h"

namespace sysinfo {
namespace network {

TEST(RoutingTableTest, TestGetRoutingTable) {
  RoutingList list;
  const bool ok = getRoutingTable(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 2);
}

}  // namespace network
}  // namespace sysinfo