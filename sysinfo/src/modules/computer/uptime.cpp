// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "modules/computer/uptime.h"

#include "base/file.h"

namespace sysinfo {
namespace computer {

bool getUptime(UptimeInfo& info) {
  QString content;
  if (!readTextFile("/proc/uptime", content)) {
    return false;
  }

  bool ok = true;
  const qint32 minutes = content.trimmed().toInt(&ok);
  if (!ok) {
    return false;
  }

  info.minutes = minutes;
  info.hours = info.minutes / 60;
  info.minutes %= 60;
  info.days = info.hours / 24;
  info.hours %= 24;
  return true;
}

}  // namespace computer
}  // namespace sysinfo