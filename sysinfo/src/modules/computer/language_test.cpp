// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/language.h"

namespace sysinfo {
namespace computer {

TEST(LanguageTest, TestGetLanguageList) {
  LanguageList list;
  const bool ok = getLanguageList(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 1);
}

}  // namespace computer
}  // namespace sysinfo