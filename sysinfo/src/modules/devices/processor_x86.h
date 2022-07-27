// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_X86_H_
#define SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_X86_H_

#include <QString>

namespace sysinfo {
namespace devices {

QString getProcessorStringFamily(const QString& vendor_id, qint32 family, qint32 model);

}  // namespace devices
}  // namespace sysinfo

#endif //SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_X86_H_
