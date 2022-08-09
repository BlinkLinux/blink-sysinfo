// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/arp_table.h"

#include <QRegularExpression>
#include <QTextStream>

#include "base/file.h"

namespace sysinfo {
namespace network {

bool getArpList(ArpList& list) {
  QString content;
  if (!readTextFile("/proc/net/arp", content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  QRegularExpression space_pattern("\\s+");

  while (stream.readLineInto(&line)) {
    if (line.startsWith("IP")) {
      continue;
    }

    const QStringList parts = line.split(space_pattern);
    if (parts.length() < 6) {
      continue;
    }
    list.append(Arp {
      .ip = parts.at(0),
      .mac = parts.at(3),
      .interface = parts.at(4),
      .hw_type = parts.at(1).toInt(nullptr, 16),
      .flags = parts.at(2).toInt(nullptr, 16),
    });
  }

  return true;
}

}  // namespace network
}  // namespace sysinfo