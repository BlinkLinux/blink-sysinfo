// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/arp_table.h"

namespace sysinfo {
namespace network {

QJsonObject dump(const Arp& arp) {
  QJsonObject obj;
  obj.insert("ip", arp.ip);
  obj.insert("mac", arp.mac);
  obj.insert("interface", arp.interface);
  obj.insert("hardwareType", arp.hw_type);
  obj.insert("flags", arp.flags);
  return obj;
}

QJsonArray dump(const ArpList& list) {
  QJsonArray array;
  for (const auto& arp : list) {
    array.append(dump(arp));
  }
  return array;
}

}  // namespace network
}  // namespace sysinfo