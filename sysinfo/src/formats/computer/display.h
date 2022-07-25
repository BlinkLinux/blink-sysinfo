// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_DISPLAY_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_DISPLAY_H_

#include <QString>
#include <QStringList>
#include <QVector>

namespace sysinfo {
namespace computer {

struct OpenGlInfo {
  QString vendor{};
  QString renderer{};
  QString version{};
  bool direct_rendering{};
};

struct Monitor {
  qint32 index{};
  qint32 width{};
  qint32 height{};
  qint32 resolution_x{};
  qint32 resolution_y{};
};

struct Display {
  qint32 width{};
  qint32 height{};

  QString vendor{};
  QString version{};
  QString xorg_version{};
  QString display_name{};
  QString current_display_monitor{};

  qint32 default_screen_number{};
  QVector<Monitor> monitors{};
  QStringList x11_extensions{};

  OpenGlInfo opengl{};
};

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_DISPLAY_H_
