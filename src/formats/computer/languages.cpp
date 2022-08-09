// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/languages.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const LanguageInfo& info) {
  QJsonObject obj;
  obj.insert("locale", info.locale);
  obj.insert("title", info.title);
  obj.insert("source", info.source);
  obj.insert("address", info.address);
  obj.insert("email", info.email);
  obj.insert("language", info.language);
  obj.insert("territory", info.territory);
  obj.insert("revision", info.revision);
  obj.insert("date", info.date);
  obj.insert("codeSet", info.code_set);
  return obj;
}

QJsonArray dump(const LanguageList& list) {
  QJsonArray array;
  for (const auto& item : list) {
    array.append(dump(item));
  }
  return array;
}

}  // namespace computer
}  // namespace sysinfo