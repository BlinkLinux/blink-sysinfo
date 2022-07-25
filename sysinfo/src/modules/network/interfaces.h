// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_NETWORK_INTERFACES_H_
#define SYSINFO_SRC_MODULES_NETWORK_INTERFACES_H_

#include "formats/network/interfaces.h"

namespace sysinfo {
namespace network {

bool getNetworkInterfaces(NetworkInterfaceList& list);

bool getNetInfo(NetworkInterface& iface);

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_NETWORK_INTERFACES_H_
