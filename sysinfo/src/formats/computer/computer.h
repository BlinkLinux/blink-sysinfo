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
#include "formats/computer/summary.h"
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
  Summary summary{};
  Uptime uptime{};
  UserList users{};
};

QJsonObject dump(const ComputerInfo& info);

constexpr const char* kNameComputer = "computer";
constexpr const char* kNameBootupList = "bootupList";
constexpr const char* kNameDevelopment = "development";
constexpr const char* kNameDisplay = "display";
constexpr const char* kNameEnvironment = "environment";
constexpr const char* kNameFilesystems = "filesystems";
constexpr const char* kNameGroups = "groups";
constexpr const char* kNameLanguages = "languages";
constexpr const char* kNameMemory = "memory";
constexpr const char* kNameModules = "modules";
constexpr const char* kNameOs = "os";
constexpr const char* kNameSummary = "summary";
constexpr const char* kNameUptime = "uptime";
constexpr const char* kNameUsers = "users";

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_COMPUTER_H_
