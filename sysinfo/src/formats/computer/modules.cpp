// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/modules.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Module& module) {
  QJsonObject obj;
  obj.insert("name", module.name);
  obj.insert("description", module.description);
  obj.insert("versionMagic", module.version_magic);
  obj.insert("aliases", QJsonArray::fromStringList(module.alias_list));
  obj.insert("path", module.path);
  obj.insert("memory", module.memory_bytes);
  obj.insert("dependencies", QJsonArray::fromStringList(module.dependencies));
  obj.insert("author", module.author);
  obj.insert("license", module.license);
  obj.insert("signer", module.signer);
  obj.insert("sigKey", module.sig_key);
  return obj;
}

QJsonArray dump(const ModuleList& list) {
  QJsonArray array;
  for (const auto& module : list) {
    array.append(dump(module));
  }

  return array;
}

}  // namespace computer
}  // namespace sysinfo