// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_LANGUAGES_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_LANGUAGES_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace computer {

struct LanguageInfo {
  QString locale{};
  QString title{};
  QString source{};
  QString address{};
  QString email{};
  QString language{};
  QString territory{};
  QString revision{};
  QString date{};
  QString code_set{};
};

using LanguageList = QVector<LanguageInfo>;

QJsonObject dump(const LanguageInfo& info);
QJsonArray dump(const LanguageList& list);

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_LANGUAGES_H_
