// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/dns_servers.h"

namespace sysinfo {
namespace network {

QJsonObject dump(const DnsServer& server) {
  QJsonObject obj;
  obj.insert("ip", server.ip);
  obj.insert("hostname", server.hostname);
  return obj;
}

QJsonArray dump(const DnsServerList& list) {
  QJsonArray array;
  for (const auto& server: list) {
    array.append(dump(server));
  }
  return array;
}

}  // namespace network
}  // namespace sysinfo