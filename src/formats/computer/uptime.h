// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace sysinfo {
namespace computer {

struct Uptime {
  qint32 days{};
  qint32 hours{};
  qint32 minutes{};
  qint32 seconds{};
};

QJsonObject dump(const Uptime& uptime);

QDebug operator<<(QDebug stream, const Uptime& info);

}  // namespace computer
}  // namespace sysinfo

Q_DECLARE_METATYPE(sysinfo::computer::Uptime)

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_UPTIME_H_
