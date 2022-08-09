// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/filesystem.h"

#include <sys/vfs.h>

#include <QDebug>
#include <QTextStream>

#include "base/file.h"

namespace sysinfo {
namespace computer {

bool getFilesystems(FilesystemList& list) {
  QString out;
  if (!readTextFile("/etc/mtab", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line;
  struct statfs sfs{};
  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(' ');
    if (parts.length() < 5) {
      continue;
    }
    Filesystem fs{};
    fs.mount_point = parts.at(1);
    if (statfs(fs.mount_point.toStdString().data(), &sfs) != 0) {
      continue;
    }
    fs.size = sfs.f_bsize * sfs.f_blocks;
    if (fs.size == 0) {
      continue;
    }
    fs.device = parts.at(0);
    fs.fs = parts.at(2);
    fs.read_only = parts.at(3) == "rw";
    fs.avail = sfs.f_bsize * sfs.f_bavail;
    fs.used_ratio = 100.0 * static_cast<double>(fs.size - fs.avail) / static_cast<double>(fs.size);
    list.append(fs);
  }

  return true;
}

}  // namespace computer
}  // namespace sysinfo