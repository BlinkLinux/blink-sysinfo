// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/display.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const OpenGlInfo& info) {
  QJsonObject obj;
  obj.insert("vendor", info.vendor);
  obj.insert("renderer", info.renderer);
  obj.insert("version", info.version);
  obj.insert("directRendering", info.direct_rendering);
  return obj;
}

QJsonObject dump(const Monitor& monitor) {
  QJsonObject obj;
  obj.insert("index", monitor.index);
  obj.insert("width", monitor.width);
  obj.insert("height", monitor.height);
  obj.insert("resolutionX", monitor.resolution_x);
  obj.insert("resolutionY", monitor.resolution_y);
  return obj;
}

QJsonObject dump(const Display& display) {
  QJsonObject obj;
  obj.insert("width", display.width);
  obj.insert("height", display.height);
  obj.insert("vendor", display.vendor);
  obj.insert("version", display.version);
  obj.insert("xorgVersion", display.xorg_version);
  obj.insert("name", display.name);
  obj.insert("currentMonitor", display.current_monitor);
  obj.insert("opengl", dump(display.opengl));
  obj.insert("defaultScreen", display.default_screen_number);

  obj.insert("x11Extensions", QJsonArray::fromStringList(display.x11_extensions));
  QJsonArray monitors;
  for (const Monitor& monitor : display.monitors) {
    monitors.append(dump(monitor));
  }
  obj.insert("monitors", monitors);

  return obj;
}

}  // namespace computer
}  // namespace sysinfo