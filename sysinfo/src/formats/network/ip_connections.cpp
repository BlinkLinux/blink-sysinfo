// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/ip_connections.h"

namespace sysinfo {
namespace network {

QString dump(IpConnectionState state) {
  switch (state) {
    case IpConnectionState::Listen: {
      return "listen";
    }
    case IpConnectionState::Established: {
      return "established";
    }
    case IpConnectionState::CloseWait: {
      return "closeWait";
    }
    default: {
      return {};
    }
  }
}

QString dump(IpConnectionProtocol protocol) {
  switch (protocol) {
    case IpConnectionProtocol::Tcp: {
      return "tcp";
    }
    case IpConnectionProtocol::Udp: {
      return "dup";
    }
    case IpConnectionProtocol::Tcp6: {
      return "tcp6";
    }
    case IpConnectionProtocol::Udp6: {
      return "udp6";
    }
    default: {
      return {};
    }
  }
}

QJsonObject dump(const IpConnection& conn) {
  QJsonObject obj;
  obj.insert("localAddress", conn.local_addr);
  obj.insert("remoteAddress", conn.remote_addr);
  obj.insert("state", dump(conn.state));
  obj.insert("protocol", dump(conn.protocol));

  obj.insert("sendPackets", conn.send_packets);
  obj.insert("receivedPackets", conn.recv_packets);

  return obj;
}

QJsonArray dump(const IpConnectionList& list) {
  QJsonArray array;
  for (const auto& conn : list) {
    array.append(dump(conn));
  }
  return array;
}

}  // namespace network
}  // namespace sysinfo