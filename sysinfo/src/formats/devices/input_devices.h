// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_INPUT_DEVICES_H_
#define SYSINFO_SRC_FORMATS_DEVICES_INPUT_DEVICES_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace devices {

enum class InputDevType : quint8 {
  Unknown = 0,
  Keyboard = 1,
  Joystick = 2,
  Mouse = 3,
  Speaker = 4,
};

struct InputDev {
  QString name{};
  InputDevType type{InputDevType::Unknown};
  qint32 bus{};
  qint32 vendor{};
  qint32 product{};
  qint32 version{};
  QString phys{};
  QString sysfs{};
};

using InputDevList = QVector<InputDev>;

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_INPUT_DEVICES_H_
