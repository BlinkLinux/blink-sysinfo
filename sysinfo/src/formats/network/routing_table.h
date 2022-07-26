// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_ROUTING_TABLE_H_
#define SYSINFO_SRC_FORMATS_NETWORK_ROUTING_TABLE_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace network {

struct Routing {
  QString destination{};
  QString gateway{};
  QString mask{};
  QString flags{};
  QString interface{};
  qint32 metric{};
  bool in_use{};
};

using RoutingList = QVector<Routing>;

QJsonObject dump(const Routing& routing);
QJsonArray dump(const RoutingList& list);

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_ROUTING_TABLE_H_
