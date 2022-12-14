// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_BASE_UNIT_H_
#define SYSINFO_SRC_BASE_UNIT_H_

#include <QString>

namespace sysinfo {

qint64 parseMemSize(const QString& s);

}  // namespace sysinfo

#endif  // SYSINFO_SRC_BASE_UNIT_H_
