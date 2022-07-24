// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/users.h"

#include <pwd.h>

namespace sysinfo {
namespace computer {

bool getUserList(UserList& list) {
  struct passwd* pw = getpwent();
  if (pw == nullptr) {
    return false;
  }

  while (pw != nullptr) {
    list.append(User{
        .name = pw->pw_name,
        .display_name = pw->pw_gecos,
        .uid = static_cast<qint32>(pw->pw_uid),
        .gid = static_cast<qint32>(pw->pw_gid),
        .home = pw->pw_dir,
        .shell = pw->pw_shell,
    });
    pw = getpwent();
  }

  endpwent();
  return true;
}

}  // namespace computer
}  // namespace sysinfo