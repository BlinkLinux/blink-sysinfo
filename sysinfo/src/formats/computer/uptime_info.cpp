// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "formats/computer/uptime_info.h"

namespace sysinfo {
namespace computer {

QDebug operator<<(QDebug stream, const UptimeInfo& info) {
  stream << "UptimeInfo {"
         << "\n  days:" << info.days
         << "\n  hours:" << info.hours
         << "\n  minutes:" << info.minutes
         << "\n  seconds:" << info.seconds
         << "\n}";
  return stream;
}


}  // namespace computer
}  // namespace sysinfo