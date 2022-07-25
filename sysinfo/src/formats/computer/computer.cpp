// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/computer.h"

#include <QJsonDocument>

namespace sysinfo {
namespace computer {

QJsonObject dump(const ComputerInfo& info) {
  QJsonObject obj;
  obj.insert("bootup", dump(info.bootup_list));
  obj.insert("development", dump(info.development));
  obj.insert("display", dump(info.display));
  obj.insert("environment", QJsonArray::fromStringList(info.environment));
  return obj;
}

QByteArray dumpToJson(const ComputerInfo& info) {
  const QJsonObject obj = dump(info);
  QJsonDocument doc;
  doc.setObject(obj);
  return doc.toJson();
}

}  // namespace computer
}  // namespace sysinfo