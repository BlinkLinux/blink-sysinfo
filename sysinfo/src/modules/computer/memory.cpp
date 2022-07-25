// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/memory.h"

#include <QDebug>
#include <QTextStream>

#include "base/file.h"
#include "base/unit.h"

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
      memory.total = parseMemSize(value);
    } else if (key == "MemFree") {
      memory.free = parseMemSize(value);
    } else if (key == "Cached") {
      memory.cached = parseMemSize(value);
    }
  }

  return true;
}

}  // namespace computer
}  // namespace sysinfo