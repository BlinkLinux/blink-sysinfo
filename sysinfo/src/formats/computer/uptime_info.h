// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_INFO_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_INFO_H_

#include <QtGlobal>

namespace sysinfo {
namespace computer {

struct UptimeInfo {
  qint32 days{};
  qint32 hours{};
  qint32 minutes{};
};

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_INFO_H_
