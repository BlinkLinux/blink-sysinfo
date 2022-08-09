// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/network/arp_table.h"

namespace sysinfo {
namespace network {

TEST(ArpTest, TestGetArpList) {
  ArpList list;
  const bool ok = getArpList(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 5);
}

}  // namespace network
}  // namespace sysinfo