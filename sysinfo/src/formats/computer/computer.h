// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_COMPUTER_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_COMPUTER_H_

#include <QJsonObject>

#include "formats/computer/boots.h"
#include "formats/computer/development.h"
#include "formats/computer/display.h"
#include "formats/computer/environment.h"
#include "formats/computer/filesystem.h"
#include "formats/computer/groups.h"
#include "formats/computer/languages.h"
#include "formats/computer/memory.h"
#include "formats/computer/modules.h"
#include "formats/computer/operation_system.h"
#include "formats/computer/uptime.h"
#include "formats/computer/users.h"

namespace sysinfo {
namespace computer {

struct ComputerInfo {
  BootupList bootup_list{};
  Development development{};
  Display display{};
  Environment environment{};
  FilesystemList fs_list{};
  GroupList groups{};
  LanguageList language_list{};
  Memory memory{};
  ModuleList module_list{};
  OperationSystem os{};
  Uptime uptime{};
  UserList users{};
};

QJsonObject dump(const ComputerInfo& info);

QByteArray dumpToJson(const ComputerInfo& info);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_COMPUTER_H_
