// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/dmi.h"

namespace sysinfo {
namespace devices {

TEST(DmiTest, TestGetSysfsRoot) {
  const QString root = dmiGetSysfsRoot();
  ASSERT_FALSE(root.isEmpty());
}

TEST(DmiTest, TestGetDmiInfo) {
  Dmi dmi;
  const bool ok = getDmiInfo(dmi);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(dmi.board.product_name.isEmpty());
}

}  // namespace devices
}  // namespace sysinfo