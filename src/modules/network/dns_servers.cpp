// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/dns_servers.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include <QDebug>

#include "base/file.h"

namespace sysinfo {
namespace network {

bool getDnsServers(DnsServerList& list) {
  QString content;
  if (!readTextFile("/etc/resolv.conf", content)) {
    return false;
  }

  const QStringList lines = content.split('\n');
  for (const auto& line: lines) {
    if (line.startsWith("nameserver")) {
      const QString domain = line.mid(static_cast<int>(strlen("nameserver"))).trimmed();
      DnsServer server{};
      server.ip = domain;
      server.hostname = getHostnameByIp(server.ip);
      list.append(server);
    }

  }

  return true;
}

QString getHostnameByIp(const QString& address) {
  struct sockaddr_in sa;
  constexpr const size_t kBufLen = 256;
  char buf[kBufLen];

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr(address.toStdString().c_str());
  if (getnameinfo((struct sockaddr*) &sa, sizeof(sa),
                  buf, kBufLen,
                  nullptr, 0, NI_NAMEREQD) == 0) {
    return QString::fromLatin1(buf, static_cast<int>(strlen(buf)));
  }

  return {};
}

}  // namespace network
}  // namespace sysinfo