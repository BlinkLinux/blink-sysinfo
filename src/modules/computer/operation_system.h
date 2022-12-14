// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_COMPUTER_OPERATION_SYSTEM_H_
#define SYSINFO_SRC_MODULES_COMPUTER_OPERATION_SYSTEM_H_

#include "formats/computer/operation_system.h"

namespace sysinfo {
namespace computer {

bool getOperationSystem(OperationSystem& os);

QString detectDistro();

QString getLanguage();

QString getLanguageCodec();

QString getLibcVersion();

QString detectKdeVersion();

QString detectGnomeVersion();

QString detectWindowManager();

QString detectXdgEnvironment(const char* env_var);

QString detectDesktopEnvironment();

QVector<double> getLoadAverage();

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_COMPUTER_OPERATION_SYSTEM_H_
