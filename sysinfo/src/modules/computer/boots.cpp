// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/boots.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getBootup(BootupList& list) {
  QString out{};
  if (!getCommandOutput("last --time-format iso", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line{};
  QRegularExpression pattern("\\s+");
  while (stream.readLineInto(&line)) {
    if (!line.contains("system boot")) {
      continue;
    }
    const QStringList parts = line.replace("system boot", "system_boot").split(pattern);
    if (parts.length() < 6) {
      qWarning() << "Invalid login record:" << line;
      continue;
    }

    Bootup bootup{};
    bootup.username = parts.at(0);
    bootup.session_tty = parts.at(1);
    bootup.kernel = parts.at(2);
    bootup.start_time = QDateTime::fromString(parts.at(3), Qt::ISODate);
    if (parts.at(4) == "still") {
      // First record.
      bootup.end_time = QDateTime::fromMSecsSinceEpoch(0);
    } else {
      bootup.end_time = QDateTime::fromString(parts.at(5), Qt::ISODate);
    }
    list.append(bootup);
  }

  return true;
}

}  // namespace computer
}  // namespace sysinfo