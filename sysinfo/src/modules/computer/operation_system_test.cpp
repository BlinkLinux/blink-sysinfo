// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/operation_system.h"

namespace sysinfo {
namespace computer {

TEST(OsTest, TestDetectDistro) {
  const QString distro = detectDistro();
  ASSERT_TRUE(distro.startsWith("Debian GNU/Linux"));
}

}  // namespace computer
}  // namespace sysinfo