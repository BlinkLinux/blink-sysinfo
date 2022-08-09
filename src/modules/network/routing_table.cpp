// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/routing_table.h"

#include <QTextStream>
#include <QRegularExpression>

#include "base/process.h"

namespace sysinfo {
namespace network {

bool getRoutingTable(RoutingList& list) {
  QString out;
  if (!getCommandOutput("route -n", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line;
  QRegularExpression space_pattern("\\s+");

  while (stream.readLineInto(&line)) {
    if (line.startsWith("Kernel") || line.startsWith("Destination")) {
      continue;
    }

    const QStringList parts = line.split(space_pattern);
    if (parts.length() < 7) {
      continue;
    }

    list.append(Routing{
        .destination = parts.at(0),
        .gateway = parts.at(1),
        .mask = parts.at(2),
        .flags = parts.at(3),
        .interface = parts.at(6),
        .metric = parts.at(4).toInt(),
        .in_use = parts.at(5) != "0",
    });
  }

  return true;
}

}  // namespace network
}  // namespace sysinfo