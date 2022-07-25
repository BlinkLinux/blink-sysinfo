// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/boots.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Bootup& bootup) {
  QJsonObject obj;
  obj.insert("username", bootup.username);
  obj.insert("sessionTty", bootup.session_tty);
  obj.insert("kernel", bootup.kernel);
  obj.insert("startTime", bootup.start_time.toSecsSinceEpoch());
  obj.insert("endTime", bootup.end_time.toSecsSinceEpoch());
  return obj;
}

QJsonArray dump(const BootupList& bootup_list) {
  QJsonArray array;
  for (const auto& bootup : bootup_list) {
    array.append(dump(bootup));
  }
  return array;
}

}  // namespace computer
}  // namespace sysinfo