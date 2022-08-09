// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/groups.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Group& group) {
  QJsonObject obj;
  obj.insert("name", group.name);
  obj.insert("gid", group.gid);
  obj.insert("members", QJsonArray::fromStringList(group.members));
  return obj;
}

QJsonArray dump(const GroupList& groups) {
  QJsonArray array;
  for (const auto& group : groups) {
    array.append(dump(group));
  }
  return array;
}

}  // namespace computer
}  // namespace sysinfo