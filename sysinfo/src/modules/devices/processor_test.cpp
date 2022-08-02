// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/processor.h"

namespace sysinfo {
namespace devices {

TEST(ProcessorTest, TestGetProcesorList) {
  Processors processors;
  const bool ok = getProcessorList(processors);
  ASSERT_TRUE(ok);
}

TEST(ProcessorTest, TestIsLittleEndian) {
  ASSERT_TRUE(isLittleEndian());
}

TEST(ProcessorTest, TestGetCache) {
  ProcessorCaches list;
  const bool ok = getProcessorCache(0, list);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(list.isEmpty());
}

}  // namespace devices
}  // namespace sysinfo