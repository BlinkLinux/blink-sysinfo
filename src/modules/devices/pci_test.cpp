// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/pci.h"

namespace sysinfo {
namespace devices {

TEST(PciTest, TestGetPciDevList) {
  PciDevList list;
  const bool ok = getPciDevList(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 3);
}

}  // namespace devices
}  // namespace sysinfo