// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/computer/modules.h"

namespace sysinfo {
namespace computer {

TEST(ModulesTest, TestGetModuleList) {
  ModuleList list;
  const bool ok = getKernelModules(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 10);
}

TEST(ModulesTest, TestGetModuleDetail) {
  Module module {.name = "stp"};
  const bool ok = getModuleDetail(module);
  ASSERT_TRUE(ok);
  ASSERT_EQ(module.dependencies, QStringList("llc"));
}

}  // namespace computer
}  // namespace sysinfo