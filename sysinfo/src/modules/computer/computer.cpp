// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/computer.h"

#include <QDebug>

#include "modules/computer/boots.h"
#include "modules/computer/development.h"
#include "modules/computer/display.h"
#include "modules/computer/environment.h"
#include "modules/computer/filesystem.h"
#include "modules/computer/groups.h"
#include "modules/computer/languages.h"
#include "modules/computer/memory.h"
#include "modules/computer/modules.h"
#include "modules/computer/operation_system.h"
#include "modules/computer/summary.h"
#include "modules/computer/uptime.h"
#include "modules/computer/users.h"

namespace sysinfo {
namespace computer {

bool getComputerInfo(ComputerInfo& info) {
  bool ok = getBootup(info.bootup_list);
  ok &= getDevelopmentEnv(info.development);  // 0.2s
  ok &= getDisplayInfo(info.display);
  info.environment = getEnvironment();
  ok &= getFilesystems(info.fs_list);
  ok &= getGroupList(info.groups);
  ok &= getLanguageList(info.language_list);
  ok &= getMemoryInfo(info.memory);
  ok &= getKernelModules(info.module_list);  // 0.6s
  ok &= getOperationSystem(info.os);  // 1.9s
  ok &= getSummary(info.summary);
  ok &= getUptime(info.uptime);
  ok &= getUserList(info.users);
  return ok;
}

bool getSpecificSection(const QString& name, QJsonObject& root) {
  QJsonObject computer;
  if (root.contains(kNameComputer)) {
    computer = root.value(kNameComputer).toObject();
  }

  if (name == kNameBootupList) {
    BootupList bootup_list;
    getBootup(bootup_list);
    computer.insert(kNameBootupList, dump(bootup_list));
  } else if (name == kNameDevelopment) {
    Development development;
    getDevelopmentEnv(development);
    computer.insert(kNameDevelopment, dump(development));
  } else if (name == kNameDisplay) {
    Display display;
    getDisplayInfo(display);
    computer.insert(kNameDisplay, dump(display));
  } else if (name == kNameEnvironment) {
    const Environment environment = getEnvironment();
    computer.insert(kNameEnvironment, QJsonArray::fromStringList(environment));
  } else if (name == kNameFilesystems) {
    FilesystemList list;
    getFilesystems(list);
    computer.insert(kNameFilesystems, dump(list));
  } else if (name == kNameGroups) {
    GroupList groups;
    getGroupList(groups);
    computer.insert(kNameGroups, dump(groups));
  } else if (name == kNameLanguages) {
    LanguageList list;
    getLanguageList(list);
    computer.insert(kNameLanguages, dump(list));
  } else if (name == kNameMemory) {
    Memory memory;
    getMemoryInfo(memory);
    computer.insert(kNameMemory, dump(memory));
  } else if (name == kNameModules) {
    ModuleList list;
    getKernelModules(list);
    computer.insert(kNameModules, dump(list));
  } else if (name == kNameOs) {
    OperationSystem os;
    getOperationSystem(os);
    computer.insert(kNameOs, dump(os));
  } else if (name == kNameSummary) {
    Summary summary;
    getSummary(summary);
    computer.insert(kNameSummary, dump(summary));
  } else if (name == kNameUptime) {
    Uptime uptime;
    getUptime(uptime);
    computer.insert(kNameUptime, dump(uptime));
  } else if (name == kNameUsers) {
    UserList list;
    getUserList(list);
    computer.insert(kNameUsers, dump(list));
  } else {
    qWarning() << "Unknown section: " << name;
    return false;
  }
  root.insert(kNameComputer, computer);

  return true;
}

}  // namespace computer
}  // namespace sysinfo