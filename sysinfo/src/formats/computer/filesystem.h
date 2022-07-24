// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_FILESYSTEM_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_FILESYSTEM_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace computer {

struct Filesystem {
  QString fs{};
  QString mount_point{};
  QString device{};
  bool read_only{};
  qint64 size{};
  qint64 avail{};
  double used_ratio{};
};

using FilesystemList = QVector<Filesystem>;

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_FILESYSTEM_H_
