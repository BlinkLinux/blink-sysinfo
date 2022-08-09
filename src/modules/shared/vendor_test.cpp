// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/shared/vendor.h"

namespace sysinfo {

TEST(VendorTest, TestGetVendorName) {
  ASSERT_EQ(getVendorName("Realtek Semiconductor Co., Ltd. RTL8821CE"), QString("Realtek"));
  ASSERT_EQ(getVendorName("Hewlett-Packard Company RTL8821CE"), QString("Hewlett-Packard"));
}

TEST(VendorTest, TestGetVendorUrl) {
  ASSERT_EQ(getVendorUrl("Realtek Semiconductor Co., Ltd. RTL8821CE"), QString("www.realtek.com.tw"));
  ASSERT_EQ(getVendorUrl("Hewlett-Packard Company RTL8821CE"), QString("www.hp.com"));
}

}  // namespace sysinfo