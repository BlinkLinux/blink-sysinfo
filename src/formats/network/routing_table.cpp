// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/network/routing_table.h"

namespace sysinfo {
namespace network {

QJsonObject dump(const Routing& routing) {
  QJsonObject obj;
  obj.insert("destination", routing.destination);
  obj.insert("gateway", routing.gateway);
  obj.insert("mask", routing.mask);
  obj.insert("flags", routing.flags);
  obj.insert("interface", routing.interface);
  obj.insert("metric", routing.metric);
  obj.insert("inUser", routing.in_use);
  return obj;
}

QJsonArray dump(const RoutingList& list) {
  QJsonArray array;
  for (const auto& routing : list) {
    array.append(dump(routing));
  }
  return array;
}

}  // namespace network
}  // namespace sysinfo