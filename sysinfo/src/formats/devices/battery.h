// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_BATTERY_H_
#define SYSINFO_SRC_FORMATS_DEVICES_BATTERY_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace devices {

struct Battery {
  QString status{};
  qint32 capacity{};
  QString capacity_level{};
  QString technology{};
  QString manufacturer{};
  QString model_name{};
  QString serial_number{};
};

using BatteryList = QVector<Battery>;

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_BATTERY_H_
