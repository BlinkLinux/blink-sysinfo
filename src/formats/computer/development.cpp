// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/development.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const DevItem& dev_item) {
  QJsonObject obj;
  obj.insert("name", dev_item.name);
  obj.insert("displayName", dev_item.display_name);
  obj.insert("version", dev_item.version);
  return obj;
}

QJsonArray dump(const DevItems& dev_items) {
  QJsonArray array;
  for (const auto& item : dev_items) {
    array.append(dump(item));
  }
  return array;
}

QJsonObject dump(const Development& development) {
  QJsonObject obj;
  obj.insert("scripting", dump(development.scripting));
  obj.insert("compilers", dump(development.compilers));
  obj.insert("tools", dump(development.tools));
  return obj;
}

}  // namespace computer
}  // namespace sysinfo