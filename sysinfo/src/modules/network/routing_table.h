// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_NETWORK_ROUTING_TABLE_H_
#define SYSINFO_SRC_MODULES_NETWORK_ROUTING_TABLE_H_

#include "formats/network/routing_table.h"

namespace sysinfo {
namespace network {

bool getRoutingTable(RoutingList& list);

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_NETWORK_ROUTING_TABLE_H_
