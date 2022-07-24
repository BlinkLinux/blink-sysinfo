// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/memory.h"

#include <QTextStream>

#include "base/file.h"

namespace sysinfo {
namespace computer {

bool getMemoryInfo(Memory& memory) {
  QString content;
  if (!readTextFile("/proc/meminfo", content)) {
    return false;
  }

  QString line{};
  QTextStream stream(&content);
  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    const QString& key = parts.at(0);
    const QString& value = parts.at(1);
    if (key == "MemTotal") {
      memory.total = getMemoryValue(value);
    } else if (key == "MemFree") {
      memory.free = getMemoryValue(value);
    } else if (key == "Cached") {
      memory.cached = getMemoryValue(value);
    }
  }

  return true;
}

qint64 getMemoryValue(const QString& value) {
  const QStringList parts = value.trimmed().split(' ');
  if (parts.length() == 1) {
    return parts.first().toLong();
  }
  if (parts.length() == 2 && parts.last() == "kB") {
    return parts.first().toLong() * 1024;
  }
  return 0;
}

}  // namespace computer
}  // namespace sysinfo