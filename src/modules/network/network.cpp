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

bool getSpecificSection(const QString& name, QJsonObject& root) {
  QJsonObject network;
  if (root.contains(kNameNetwork)) {
    network = root.value(kNameNetwork).toObject();
  }
  if (name == kNameArp) {
    ArpList list;
    getArpList(list);
    network.insert(kNameArp, dump(list));
  } else if (name == kNameDns) {
    DnsServerList list;
    getDnsServers(list);
    network.insert(kNameDns, dump(list));
  } else if (name == kNameInterfaces) {
    NetworkInterfaceList list;
    getNetworkInterfaces(list);
    network.insert(kNameInterfaces, dump(list));
  } else if (name == kNameConnections) {
    IpConnectionList list;
    getIpConnectionList(list);
    network.insert(kNameConnections, dump(list));
  } else if (name == kNameRoutingTable) {
    RoutingList list;
    getRoutingTable(list);
    network.insert(kNameRoutingTable, dump(list));
  } else {
    qWarning() << "Unknown section:" << name;
    return false;
  }

  root.insert(kNameNetwork, network);

  return true;
}

}  // namespace network
}  // namespace sysinfo