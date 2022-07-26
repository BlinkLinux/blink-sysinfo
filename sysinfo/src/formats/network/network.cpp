// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/network.h"

namespace sysinfo {
namespace network {

QJsonObject network::dump(const NetworkInfo& info) {
  QJsonObject obj;
  obj.insert("arpList", dump(info.arp_list));
  obj.insert("dnsList", dump(info.dns_list));
  obj.insert("interfaces", dump(info.iface_list));
  obj.insert("connections", dump(info.connection_list));
  obj.insert("routingTable", dump(info.routing_table));
  return obj;
}

}  // namespace network
}  // namespace sysinfo