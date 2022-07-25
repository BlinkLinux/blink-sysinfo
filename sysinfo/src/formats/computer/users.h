// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_USERS_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_USERS_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace computer {

struct User {
  QString name{};
  QString display_name{};
  qint32 uid{};
  qint32 gid{};
  QString home{};
  QString shell{};
};

using UserList = QVector<User>;

QJsonObject dump(const User& user);
QJsonArray dump(const UserList& list);

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_USERS_H_
