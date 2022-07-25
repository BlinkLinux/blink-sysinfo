// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/computer.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const ComputerInfo& info) {
  QJsonObject obj;
  obj.insert("bootupList", dump(info.bootup_list));
  obj.insert("development", dump(info.development));
  obj.insert("display", dump(info.display));
  obj.insert("environment", QJsonArray::fromStringList(info.environment));
  obj.insert("filesystems", dump(info.fs_list));
  obj.insert("groups", dump(info.groups));
  obj.insert("languages", dump(info.language_list));
  obj.insert("memory", dump(info.memory));
  obj.insert("modules", dump(info.module_list));
  obj.insert("os", dump(info.os));
  obj.insert("uptime", dump(info.uptime));
  obj.insert("users", dump(info.users));
  return obj;
}

}  // namespace computer
}  // namespace sysinfo