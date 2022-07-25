// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_BASE_STRING_H_
#define SYSINFO_SRC_BASE_STRING_H_

#include <QString>
#include <QStringList>

namespace sysinfo {

QStringList splitEmptyParts(const QString& s);

}  // namespace sysinfo

#endif  // SYSINFO_SRC_BASE_STRING_H_
