// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_H_
#define SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_H_

#include "formats/devices/processor.h"

namespace sysinfo {
namespace devices {

bool getProcessorList(Processors& processors);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_DEVICES_PROCESSOR_H_
