// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_MODULES_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_MODULES_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QVector>

namespace sysinfo {
namespace computer {

struct Module {
  QString name{};
  QString description{};
  QString version_magic{};

  QString path{};
  qint32 memory_bytes{};

  QStringList dependencies{};

  QString author{};
  QString license{};

  QString signer{};
  QString sig_key{};
};

using ModuleList = QVector<Module>;

QJsonObject dump(const Module& module);
QJsonArray dump(const ModuleList& list);

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_MODULES_H_
