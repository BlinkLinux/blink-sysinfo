// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_DEVELOPMENT_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_DEVELOPMENT_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace computer {

struct DevItem {
  QString name{};
  QString display_name{};
  QString version{};
};

using DevItems = QVector<DevItem>;

struct Development {
  DevItems scripting{};
  DevItems compilers{};
  DevItems tools{};
};

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_DEVELOPMENT_H_
