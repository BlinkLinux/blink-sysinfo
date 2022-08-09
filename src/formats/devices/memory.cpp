// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/memory.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const MemoryInfos& memory) {
  QJsonObject obj;
  for (auto it = memory.cbegin(); it != memory.cend(); ++it) {
    obj.insert(it.key(), it.value());
  }
  return obj;
}

}  // namespace devices
}  // namespace sysinfo