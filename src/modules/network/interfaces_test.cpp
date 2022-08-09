// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/network/interfaces.h"

namespace sysinfo {
namespace network {

TEST(InterfacesTest, TestGetIfaceList) {
  NetworkInterfaceList list;
  const bool ok = getNetworkInterfaces(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 3);
}

TEST(InterfacesTest, TestGetIfaceType) {
  ASSERT_EQ(getIfaceType("enp2s0"), NetworkInterfaceType::Ethernet);
  ASSERT_EQ(getIfaceType("wlp3s0"), NetworkInterfaceType::Wireless);
  ASSERT_EQ(getIfaceType("docker0"), NetworkInterfaceType::Bridge);
  ASSERT_EQ(getIfaceType("veth7f9c13"), NetworkInterfaceType::VirtualNetwork);
}

}  // namespace network
}  // namespace sysinfo