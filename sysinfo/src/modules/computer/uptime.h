// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_COMPUTER_UPTIME_H_
#define SYSINFO_SRC_MODULES_COMPUTER_UPTIME_H_

#include "formats/computer/uptime_info.h"

namespace sysinfo {
namespace computer {

bool getUptime(UptimeInfo& info);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_COMPUTER_UPTIME_H_
