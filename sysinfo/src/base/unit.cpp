// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "base/unit.h"

#include <QRegularExpression>

namespace sysinfo {

qint64 parseMemSize(const QString& s) {
  const QString s2 = s.toLower().remove('b').trimmed();
  qint64 size = 0;
  for (const QChar chr : s2) {
    const char c = chr.toLatin1();
    if (c >= '0' && c <= '9') {
      size = 10 * size + (c - '0');
      continue;
    }
    switch (c) {
      case 'k': {
        size *= (1 << 10);
        break;
      }
      case 'm': {
        size *= (1 << 20);
        break;
      }
      case 'g': {
        size *= (1 << 30);
        break;
      }
      case 't': {
        size *= (static_cast<qint64>(1) << 40);
        break;
      }
      default: {
        break;
      }
    }
  }

  return size;
}

}  // namespace sysinfo