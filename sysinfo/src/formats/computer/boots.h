// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_BOOTS_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_BOOTS_H_

#include <QDateTime>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace computer {

struct Bootup {
  QString username{};
  QString session_tty{};
  QString kernel{};
  QDateTime start_time{};
  QDateTime end_time;
};

using BootupList = QVector<Bootup>;

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_BOOTS_H_
