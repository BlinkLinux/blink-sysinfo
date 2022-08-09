// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_SHARED_VENDOR_H_
#define SYSINFO_SRC_MODULES_SHARED_VENDOR_H_

#include <QString>

namespace sysinfo {

QString getVendorName(const QString& id);

QString getVendorUrl(const QString& id);

}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_SHARED_VENDOR_H_
