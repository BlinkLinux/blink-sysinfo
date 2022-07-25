// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_INTERFACES_H_
#define SYSINFO_SRC_FORMATS_NETWORK_INTERFACES_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace network {

enum class NetworkInterfaceType : quint8 {
  Unknown = 0,
  Loopback = 1,
  Ethernet = 2,
  Wireless = 3,
  Bridge = 4,
  PointToPoint = 5,
  Bluetooth = 6,
  VirtualNetwork = 7,
  Mesh = 8,
};

struct NetworkInterface {
  QString interface{};
  QString ip{};
  QString mac{};
  QString mask{};
  QString broadcast{};

  qint32 mtu{};
  qint64 sent{};
  qint64 received{};
  NetworkInterfaceType type{};
};

using NetworkInterfaceList = QVector<NetworkInterface>;

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_INTERFACES_H_
