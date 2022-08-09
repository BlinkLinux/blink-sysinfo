// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_NETWORK_H_
#define SYSINFO_SRC_FORMATS_NETWORK_NETWORK_H_

#include <QJsonObject>

#include "formats/network/arp_table.h"
#include "formats/network/dns_servers.h"
#include "formats/network/interfaces.h"
#include "formats/network/ip_connections.h"
#include "formats/network/routing_table.h"

namespace sysinfo {
namespace network {

struct NetworkInfo {
  ArpList arp_list{};
  DnsServerList dns_list{};
  NetworkInterfaceList iface_list{};
  IpConnectionList connection_list{};
  RoutingList routing_table{};
};

QJsonObject dump(const NetworkInfo& info);

constexpr const char* kNameNetwork = "network";
constexpr const char* kNameArp = "arp";
constexpr const char* kNameDns = "dns";
constexpr const char* kNameInterfaces = "interfaces";
constexpr const char* kNameConnections = "connections";
constexpr const char* kNameRoutingTable = "routingTable";

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_NETWORK_H_
