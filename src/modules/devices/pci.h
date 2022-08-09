// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_PCI_H_
#define SYSINFO_SRC_MODULES_DEVICES_PCI_H_

#include "formats/devices/pci.h"

namespace sysinfo {
namespace devices {

bool getPciDevList(PciDevList& list);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_DEVICES_PCI_H_
