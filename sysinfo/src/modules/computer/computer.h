// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_COMPUTER_COMPUTER_H_
#define SYSINFO_SRC_MODULES_COMPUTER_COMPUTER_H_

#include "formats/computer/computer.h"

namespace sysinfo {
namespace computer {

bool getComputerInfo(ComputerInfo& info);

bool getSpecificSection(const QString& name, QJsonObject& root);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_COMPUTER_COMPUTER_H_
