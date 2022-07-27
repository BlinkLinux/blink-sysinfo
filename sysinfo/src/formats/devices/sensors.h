// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_SENSORS_H_
#define SYSINFO_SRC_FORMATS_DEVICES_SENSORS_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace devices {

struct Sensor {
  QString name{};
  QString driver_path{};
  QString mon_name{};
  QString friendly_name{};
  QString unit{};
  double value{};
};

using Sensors = QVector<Sensor>;

QJsonObject dump(const Sensor& sensor);
QJsonArray dump(const Sensors& list);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_SENSORS_H_
