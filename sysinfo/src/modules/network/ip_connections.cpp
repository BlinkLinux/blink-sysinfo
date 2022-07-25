// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/ip_connections.h"

#include <QDebug>
#include <QTextStream>
#include <QRegularExpression>

#include "base/process.h"

namespace sysinfo {
namespace network {

bool getIpConnectionList(IpConnectionList& list) {
  QString out;
  if (!getCommandOutput("netstat -an", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line;
  QRegularExpression space_pattern("\\s+");

  while (stream.readLineInto(&line)) {
    if (!line.startsWith("tcp") && !line.startsWith("udp")) {
      continue;
    }
    const QStringList parts = line.split(space_pattern);
    if (parts.length() < 6) {
      continue;
    }

    IpConnection conn;
    const QString& protocol = parts.at(0);
    if (protocol == "tcp") {
      conn.protocol = IpConnectionProtocol::Tcp;
    } else if (protocol == "tcp6") {
      conn.protocol = IpConnectionProtocol::Tcp6;
    } else if (protocol == "udp") {
      conn.protocol = IpConnectionProtocol::Udp;
    } else if (protocol == "udp6") {
      conn.protocol = IpConnectionProtocol::Udp6;
    }
    conn.recv_packets = parts.at(1).toLong();
    conn.send_packets = parts.at(2).toLong();
    conn.local_addr = parts.at(3);
    conn.remote_addr = parts.at(4);
    const QString& state = parts.at(5);
    if (state == "LISTEN") {
      conn.connection_state = IpConnectionState::Listen;
    } else if (state == "CLOSE_WAIT") {
      conn.connection_state = IpConnectionState::CloseWait;
    } else if (state == "ESTABLISHED") {
      conn.connection_state = IpConnectionState::Established;
    }
    list.append(conn);
  }

  return true;
}

}  // namespace network
}  // namespace sysinfo