// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_NETWORK_DNS_SERVERS_H_
#define SYSINFO_SRC_MODULES_NETWORK_DNS_SERVERS_H_

#include "formats/network/dns_servers.h"

namespace sysinfo {
namespace network {

bool getDnsServers(DnsServerList& list);

QString getHostnameByIp(const QString& address);

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_NETWORK_DNS_SERVERS_H_
