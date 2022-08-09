// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_IP_CONNECTIONS_H_
#define SYSINFO_SRC_FORMATS_NETWORK_IP_CONNECTIONS_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace network {

enum class IpConnectionState : quint8 {
  Nil = 0,
  Listen = 1,
  Established = 2,
  CloseWait = 3,
};

enum class IpConnectionProtocol : quint8 {
  Tcp = 0,
  Udp = 1,
  Tcp6 = 2,
  Udp6 = 3,
};

struct IpConnection {
  QString local_addr{};
  QString remote_addr{};
  IpConnectionState state{IpConnectionState::Nil};
  IpConnectionProtocol protocol{};

  qint64 send_packets{};
  qint64 recv_packets{};
};

using IpConnectionList = QVector<IpConnection>;

QString dump(IpConnectionState state);
QString dump(IpConnectionProtocol protocol);
QJsonObject dump(const IpConnection& conn);
QJsonArray dump(const IpConnectionList& list);

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_IP_CONNECTIONS_H_
