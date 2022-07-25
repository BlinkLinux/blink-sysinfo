// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "base/string.h"

namespace sysinfo {

QStringList splitEmptyParts(const QString& s) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  return s.split(' ', Qt::SkipEmptyParts);
#else
  return s.split(' ', QString::SkipEmptyParts);
#endif
}

}  // namespace sysinfo