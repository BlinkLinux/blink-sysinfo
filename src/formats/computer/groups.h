// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_GROUPS_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_GROUPS_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QVector>

namespace sysinfo {
namespace computer {

struct Group {
  QString name{};
  qint32 gid{};
  QStringList members{};
};

using GroupList = QVector<Group>;

QJsonObject dump(const Group& group);
QJsonArray dump(const GroupList& groups);

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_GROUPS_H_
