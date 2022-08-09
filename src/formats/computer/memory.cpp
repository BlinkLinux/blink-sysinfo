// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/memory.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Memory& memory) {
  QJsonObject obj;
  obj.insert("total", memory.total);
  obj.insert("free", memory.free);
  obj.insert("cached", memory.cached);
  return obj;
}

}  // namespace computer
}  // namespace sysinfo