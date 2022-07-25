// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "formats/computer/uptime.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Uptime& uptime) {
  QJsonObject obj;
  obj.insert("days", uptime.days);
  obj.insert("hours", uptime.hours);
  obj.insert("minutes", uptime.minutes);
  obj.insert("seconds", uptime.seconds);
  return obj;
}

QDebug operator<<(QDebug stream, const Uptime& info) {
  stream << "Uptime {"
         << "\n  days:" << info.days
         << "\n  hours:" << info.hours
         << "\n  minutes:" << info.minutes
         << "\n  seconds:" << info.seconds
         << "\n}";
  return stream;
}

}  // namespace computer
}  // namespace sysinfo