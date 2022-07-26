// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/input_devices.h"

namespace sysinfo {
namespace devices {

QString dump(InputDevType type) {
  switch (type) {
    case InputDevType::Unknown: {
      return "unknown";
    }
    case InputDevType::Keyboard: {
      return "keyboard";
    }
    case InputDevType::Joystick: {
      return "joystick";
    }
    case InputDevType::Mouse: {
      return "mouse";
    }
    case InputDevType::Speaker: {
      return "speaker";
    }
    default: {
      return {};
    }
  }
}

QJsonObject dump(const InputDev& dev) {
  QJsonObject obj;
  obj.insert("name", dev.name);
  obj.insert("type", dump(dev.type));
  obj.insert("bus", dev.bus);
  obj.insert("vendor", dev.vendor);
  obj.insert("product", dev.product);
  obj.insert("version", dev.version);
  obj.insert("phys", dev.phys);
  obj.insert("sysfs", dev.sysfs);
  return obj;
}

QJsonArray dump(const InputDevList& list) {
  QJsonArray array;
  for (const auto& dev : list) {
    array.append(dump(dev));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo