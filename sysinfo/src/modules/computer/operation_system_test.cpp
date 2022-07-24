// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>
#include <QDebug>

#include "modules/computer/operation_system.h"

namespace sysinfo {
namespace computer {

TEST(OsTest, TestDetectDistro) {
  const QString distro = detectDistro();
  ASSERT_TRUE(distro.startsWith("Debian GNU/Linux"));
}

TEST(OsTest, TestGetLanguage) {
  const QString language = getLanguage();
  ASSERT_FALSE(language.isEmpty());
}

TEST(OsTest, TestGetLanguageCodec) {
  const QString lang_codec = getLanguageCodec();
  ASSERT_FALSE(lang_codec.isEmpty());
  qDebug() << "lang_codec:" << lang_codec;
  ASSERT_TRUE(lang_codec.contains("UTF-8"));
}

TEST(OsTest, TestGetLibc) {
  const QString libc = getLibcVersion();
  ASSERT_FALSE(libc.isEmpty());
  ASSERT_TRUE(libc.startsWith("GNU C Library"));
}

TEST(OsTest, TestDesktopEnvironment) {
  const QString desktop = detectDesktopEnvironment();
  qDebug() << "desktop:" << desktop;
  ASSERT_FALSE(desktop.isEmpty());
}

TEST(OsTest, TestLoadAverage) {
  const auto& list = getLoadAverage();
  qDebug() << "load avg:" << list;
  ASSERT_EQ(list.length(), 3);
}

}  // namespace computer
}  // namespace sysinfo