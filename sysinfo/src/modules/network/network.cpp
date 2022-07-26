// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/network.h"

#include "modules/network/arp_table.h"
#include "modules/network/dns_servers.h"
#include "modules/network/interfaces.h"
#include "modules/network/ip_connections.h"
#include "modules/network/routing_table.h"

namespace sysinfo {
namespace network {

bool getNetworkInfo(NetworkInfo& info) {
  bool ok = true;
  ok &= getArpList(info.arp_list);
  ok &= getDnsServers(info.dns_list);
  ok &= getNetworkInterfaces(info.iface_list);
  ok &= getIpConnectionList(info.connection_list);
  ok &= getRoutingTable(info.routing_table);
  return ok;
}

}  // namespace network
}  // namespace sysinfo