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

}  // namespace network
}  // namespace sysinfo