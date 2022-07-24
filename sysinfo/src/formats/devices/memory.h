// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_MEMORY_H_
#define SYSINFO_SRC_FORMATS_DEVICES_MEMORY_H_

#include <QMap>
#include <QString>

namespace sysinfo {
namespace devices {

using MemoryInfos = QMap<QString, qint64>;

}  // namespace devices
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_DEVICES_MEMORY_H_
