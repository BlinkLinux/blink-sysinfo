// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_COMPUTER_SUMMARY_H_
#define SYSINFO_SRC_MODULES_COMPUTER_SUMMARY_H_

#include "formats/computer/summary.h"

namespace sysinfo {
namespace computer {

bool getSummary(Summary& summary);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_COMPUTER_SUMMARY_H_
