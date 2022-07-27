// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/computer.h"

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

}  // namespace computer
}  // namespace sysinfo