// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/interfaces.h"

namespace sysinfo {
namespace network {

QString dump(NetworkInterfaceType type) {
  switch (type) {
    case NetworkInterfaceType::Unknown: {
      return "unknown";
    }
    case NetworkInterfaceType::Loopback: {
      return "loopback";
    }
    case NetworkInterfaceType::Ethernet: {
      return "ethernet";
    }
    case NetworkInterfaceType::Wireless: {
      return "wireless";
    }
    case NetworkInterfaceType::Bridge: {
      return "bridge";
    }
    case NetworkInterfaceType::PointToPoint: {
      return "p2p";
    }
    case NetworkInterfaceType::Bluetooth: {
      return "bluetooth";
    }
    case NetworkInterfaceType::VirtualNetwork: {
      return "virtualNetwork";
    }
    case NetworkInterfaceType::Mesh: {
      return "mesh";
    }
    default: {
      return {};
    }
  }
}

QJsonObject dump(const NetworkInterface& iface) {
  QJsonObject obj;
  obj.insert("interface", iface.interface);
  obj.insert("ip", iface.ip);
  obj.insert("mac", iface.mac);
  obj.insert("mask", iface.mask);
  obj.insert("broadcast", iface.broadcast);

  obj.insert("mtu", iface.mtu);
  obj.insert("sent", iface.sent);
  obj.insert("received", iface.received);
  obj.insert("type", dump(iface.type));

  return obj;
}

QJsonArray dump(const NetworkInterfaceList& list) {
  QJsonArray array;
  for (const auto& iface : list) {
    array.append(dump(iface));
  }
  return array;
}

}  // namespace network
}  // namespace sysinfo