// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/memory.h"

#include <QDebug>
#include <QTextStream>

#include "base/file.h"
#include "base/unit.h"

namespace sysinfo {
namespace devices {

bool getMemoryInfo(MemoryInfos& map) {
  QString content;
  if (!readTextFile("/proc/meminfo", content)) {
    return false;
  }

  QString line;
  QTextStream stream(&content);
  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    if (parts.length() != 2) {
      continue;
    }
    const qint64 value = parseMemSize(parts.at(1));
    map.insert(parts.at(0), value);
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo