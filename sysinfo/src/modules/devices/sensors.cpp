// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/sensors.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include "base/file.h"
#include "base/string.h"

namespace sysinfo {
namespace devices {
namespace {

constexpr const char* kHwmonPrefix[] = {"device", ""};

QString getSensorPath(int number, const char* prefix) {
  return QString::asprintf("/sys/class/hwmon/hwmon%d/%s", number, prefix);
}

QString determineDriverForHwmonPath(const QString& path) {
  QFileInfo info;

  info = QString("%1/device/driver").arg(path);
  if (info.exists()) {
    return info.canonicalFilePath();
  }

  info = QString("%1/device").arg(path);
  if (info.exists()) {
    return info.canonicalFilePath();
  }

  info = QString("%1/name").arg(path);
  if (info.exists()) {
    return info.canonicalFilePath();
  }

  return {};
}

struct HwmonSensor {
  const char* friendly_name;
  const char* path_format;
  const char* key_format;
  const char* unit;
  const float adjust_ratio;
  const int begin_at;
};

static const struct HwmonSensor kHwmonSensors[] = {
    {
        "Fan",
        "%s/fan%d_input",
        "fan%d",
        "RPM",
        1.0,
        1
    },
    {
        "Temperature",
        "%s/temp%d_input",
        "temp%d",
        "\302\260C",
        1000.0,
        1
    },
    {
        "Voltage",
        "%s/in%d_input",
        "in%d",
        "V",
        1000.0,
        0
    },
};

}  // namespace

bool getSensorList(Sensors& list) {
  // TODO(Shaohua): Support other methods.
  return readSensorsHwmon(list);
}

bool readSensorsHwmon(Sensors& list) {
  for (const char* prefix: kHwmonPrefix) {
    for (int hwmon = 0; /**/; ++hwmon) {
      const QString hwmon_path = getSensorPath(hwmon, prefix);
      if (!QFileInfo::exists(hwmon_path)) {
        break;
      }
      const QString driver = determineDriverForHwmonPath(hwmon_path);

      for (const auto& sensor: kHwmonSensors) {
        for (int count = sensor.begin_at; /**/; ++count) {
          const QString sensor_path = QString::asprintf(sensor.path_format,
                                                        hwmon_path.toStdString().c_str(), count);
          if (!QFileInfo::exists(sensor_path)) {
            if (count < 256) {
              // brute-force find all.
              continue;
            } else {
              break;
            }
          }
          const QString content = readTextFile(sensor_path);
          const double value = content.toDouble() / sensor.adjust_ratio;

          const QString mon_name = QString::asprintf(sensor.key_format, count);
          QString name = QString("%1/%2").arg(QFileInfo(driver).fileName(), mon_name);
//          qDebug() << "Add sensor: friendly_name:" << sensor.friendly_name << ", name:" << name
//                   << ", unit:" << sensor.unit << ", value:" << value;

          list.append(Sensor{
              .name = name,
              .driver_path = driver,
              .mon_name = mon_name,
              .friendly_name = sensor.friendly_name,
              .unit = sensor.unit,
              .value = value,
          });
        }
      }
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo