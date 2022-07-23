// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "modules/computer/uptime.h"

#include <QDebug>

#include "base/file.h"

namespace sysinfo {
namespace computer {

bool getUptime(UptimeInfo& info) {
  QString content;
  if (!readTextFile("/proc/uptime", content)) {
    qWarning() << "Failed to read uptime file!";
    return false;
  }

  bool ok = true;
  const auto uptime_str = content.splitRef(" ").at(0);
  const double seconds = uptime_str.toDouble(&ok);
  if (!ok) {
    qWarning() << "Failed to convert uptime to integer";
    return false;
  }

  info.seconds = static_cast<qint32>(seconds);
  info.minutes = info.seconds / 60;
  info.seconds %= 60;
  info.hours = info.minutes / 60;
  info.minutes %= 60;
  info.days = info.hours / 24;
  info.hours %= 24;
  return true;
}

}  // namespace computer
}  // namespace sysinfo