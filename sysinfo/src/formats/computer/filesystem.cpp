// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/filesystem.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Filesystem& fs) {
  QJsonObject obj;
  obj.insert("filesystem", fs.fs);
  obj.insert("mountPoint", fs.mount_point);
  obj.insert("device", fs.device);
  obj.insert("size", fs.size);
  obj.insert("available", fs.avail);
  obj.insert("usedRatio", fs.used_ratio);
  obj.insert("readOnly", fs.read_only);
  return obj;
}

QJsonArray dump(const FilesystemList& list) {
  QJsonArray array;
  for (const auto& item : list) {
    array.append(dump(item));
  }
  return array;
}

}  // namespace computer
}  // namespace sysinfo