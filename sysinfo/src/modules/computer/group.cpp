// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/group.h"

#include <sys/types.h>
#include <grp.h>

namespace sysinfo {
namespace computer {

bool getGroupList(GroupList& list) {
  struct group* gr = getgrent();
  if (gr == nullptr) {
    return false;
  }

  while (gr != nullptr) {
    Group group{
        .name = gr->gr_name,
        .gid = static_cast<qint32>(gr->gr_gid),
    };

    if (gr->gr_mem != nullptr && *gr->gr_mem != nullptr) {
      for (int i = 0; gr->gr_mem[i] != nullptr; ++i) {
        const char* name = gr->gr_mem[i];
        printf("name: %s\n", name);
        group.members.append(name);
      }
    }

    list.append(group);
    gr = getgrent();
  }


  endgrent();
  return true;
}

}  // namespace computer
}  // namespace sysinfo