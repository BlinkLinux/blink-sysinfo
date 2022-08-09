// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include <QDebug>

#include "modules/devices/processor_x86.h"

namespace sysinfo {
namespace devices {

TEST(ProcessorX86Test, TestGetStringFamily) {
  const QString family_str = getProcessorStringFamily("GenuineIntel", 6, 165);
  ASSERT_EQ(family_str, QString("Pentium III/Pentium III Xeon/Celeron/Core Duo/Core Duo 2"));
}

}  // namespace devices
}  // namespace sysinfo