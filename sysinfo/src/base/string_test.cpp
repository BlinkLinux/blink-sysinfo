// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include <QDebug>

#include "base/string.h"

namespace sysinfo {

TEST(StringTest, TestSplitEmptyParts) {
  QStringList parts = splitEmptyParts(" hello  world ");
  ASSERT_EQ(parts.length(), 2);
  parts = splitEmptyParts(" hello \tworld ");
  ASSERT_EQ(parts.length(), 3);
}

}  // namespace sysinfo