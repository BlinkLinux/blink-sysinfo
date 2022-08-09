// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/users.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const User& user) {
  QJsonObject obj;
  obj.insert("name", user.name);
  obj.insert("displayName", user.display_name);
  obj.insert("uid", user.uid);
  obj.insert("gid", user.gid);
  obj.insert("home", user.home);
  obj.insert("shell", user.shell);
  return obj;
}

QJsonArray dump(const UserList& list) {
  QJsonArray array;
  for (const auto& user : list) {
    array.append(dump(user));
  }
  return array;
}

}  // namespace computer
}  // namespace sysinfo
