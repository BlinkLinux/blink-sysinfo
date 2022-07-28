// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/computer.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const ComputerInfo& info) {
  QJsonObject obj;
  obj.insert(kNameBootupList, dump(info.bootup_list));
  obj.insert(kNameDevelopment, dump(info.development));
  obj.insert(kNameDisplay, dump(info.display));
  obj.insert(kNameEnvironment, QJsonArray::fromStringList(info.environment));
  obj.insert(kNameFilesystems, dump(info.fs_list));
  obj.insert(kNameGroups, dump(info.groups));
  obj.insert(kNameLanguages, dump(info.language_list));
  obj.insert(kNameMemory, dump(info.memory));
  obj.insert(kNameModules, dump(info.module_list));
  obj.insert(kNameOs, dump(info.os));
  obj.insert(kNameSummary, dump(info.summary));
  obj.insert(kNameUptime, dump(info.uptime));
  obj.insert(kNameUsers, dump(info.users));
  return obj;
}

}  // namespace computer
}  // namespace sysinfo