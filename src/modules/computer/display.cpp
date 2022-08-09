// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/display.h"

#include <QGuiApplication>
#include <QRegularExpressionMatch>
#include <QScreen>
#include <QTextStream>

#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getDisplayInfo(Display& display) {
  QScreen* screen = QGuiApplication::primaryScreen();
  if (screen == nullptr) {
    return false;
  }
  const QSize size = screen->size();
  display.width = size.width();
  display.height = size.height();

  bool ok = getGlxInfo(display.opengl);
  ok &= getX11Info(display);
  return ok;
}

bool getGlxInfo(OpenGlInfo& gl) {
  QString out;
  if (!getCommandOutput("glxinfo", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line{};
  while (stream.readLineInto(&line)) {
    const int semi_index = line.indexOf(':');
    if (line.startsWith("direct rendering")) {
      gl.direct_rendering = line.contains("Yes");
    } else if (line.startsWith("OpenGL vendor string")) {
      if (semi_index > 0) {
        gl.vendor = line.mid(semi_index + 1).trimmed();
      }
    } else if (line.startsWith("OpenGL renderer string")) {
      if (semi_index > 0) {
        gl.renderer = line.mid(semi_index + 1).trimmed();
      }
    } else if (line.startsWith("OpenGL version str")) {
      if (semi_index > 0) {
        gl.version = line.mid(semi_index + 1).trimmed();
      }
    }
  }

  return true;
}

bool getX11Info(Display& display) {
  QString out;
  if (!getCommandOutput("xdpyinfo", out)) {
    return false;
  }
  QTextStream stream(&out);
  QString line{};
  bool read_header{true};
  QRegularExpression size_pattern("(\\d+)x(\\d+)");

  while (stream.readLineInto(&line)) {
    if (read_header) {
      const int semi_index = line.indexOf(':');
      if (semi_index == -1) {
        continue;
      }

      const QString key = line.left(semi_index);
      const QString value = line.mid(semi_index + 1);

      if (key == "name of display") {
        display.name = value;
      } else if (key == "version number") {
        display.version = value;

      } else if (key == "vendor string") {
        display.vendor = value;
      } else if (key == "X.Org version") {
        display.xorg_version = value;
      } else if (key == "number of extensions") {
        const int number_extensions = value.trimmed().toInt();
        for (int i = 0; i < number_extensions; ++i) {
          if (stream.readLineInto(&line)) {
            display.x11_extensions.append(line.trimmed());
          }
        }
      } else if (key == "default screen number") {
        display.default_screen_number = value.toInt();
        read_header = false;
      }

      continue;
    }

    // Read monitors.
    const int semi_index = line.indexOf(':');
    if (semi_index == -1) {
      continue;
    }

    const QString key = line.left(semi_index);
    const QString value = line.mid(semi_index + 1).trimmed();
    if (key == "  dimensions") {
      const auto match = size_pattern.match(value);
      if (match.isValid()) {
        const int width = match.captured(1).toInt();
        const int height = match.captured(2).toInt();
        display.monitors.append(Monitor{
            .index = display.monitors.length(),
            .width = width,
            .height = height,
        });
      }
    } else if (key == "  resolution") {
      const auto match = size_pattern.match(value);
      if (match.isValid()) {
        display.monitors.last().resolution_x = match.captured(1).toInt();
        display.monitors.last().resolution_y = match.captured(2).toInt();
      }
    }
  }

  return true;
}

}  // namespace computer
}  // namespace sysinfo