// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/input_devices.h"

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool getInputDevices(InputDevList& list) {
  QString content;
  if (!readTextFile("/proc/bus/input/devices", content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  InputDev dev{};
  while (stream.readLineInto(&line)) {
    if (line.isEmpty()) {
      // End of last dev info.
      list.append(dev);
      dev = InputDev{};
      continue;
    }

    switch (line.at(0).toLatin1()) {
      case 'I': {
        sscanf(line.toStdString().c_str(), "I: Bus=%x Vendor=%x Product=%x Version=%x",
               &dev.bus, &dev.vendor, &dev.product, &dev.version);
        break;
      }
      case 'N': {
        dev.name = line.mid(static_cast<int>(strlen("N: Name="))).remove('"');
        if (dev.name.contains("PC Speaker")) {
          dev.type = InputDevType::Speaker;
        }
        break;
      }
      case 'P': {
        dev.phys = line.mid(static_cast<int>(strlen("P: Phys=")));
        break;
      }
      case 'S': {
        dev.sysfs = line.mid(static_cast<int>(strlen("S: Sysfs=")));
        break;
      }
      case 'U': {
        break;
      }
      case 'H': {
        if (line.contains("kbd")) {
          dev.type = InputDevType::Keyboard;
        } else if (line.contains("js")) {
          dev.type = InputDevType::Joystick;
        } else if (line.contains("mouse")) {
          dev.type = InputDevType::Mouse;
        }
        break;
      }
      default: {
        // Ignore
      }
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo