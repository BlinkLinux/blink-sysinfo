// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/network.h"

namespace sysinfo {
namespace network {

QJsonObject dump(const NetworkInfo& info) {
  QJsonObject obj;
  obj.insert(kNameArp, dump(info.arp_list));
  obj.insert(kNameDns, dump(info.dns_list));
  obj.insert(kNameInterfaces, dump(info.iface_list));
  obj.insert(kNameConnections, dump(info.connection_list));
  obj.insert(kNameRoutingTable, dump(info.routing_table));
  return obj;
}

}  // namespace network
}  // namespace sysinfo