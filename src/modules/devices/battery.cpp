// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/battery.h"

#include <QDir>
#include <QFileInfo>

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool getBatteryInfo(BatteryList& list) {
  scanBatterySysfs(list);
  return true;
}

bool scanBatterySysfs(BatteryList& list) {
  QDir dir("/sys/class/power_supply");
  if (!dir.exists()) {
    return false;
  }

  for (const QFileInfo& info : dir.entryInfoList(QDir::NoDotAndDotDot)) {
    if (!info.isDir()) {
      continue;
    }
    if (!info.fileName().startsWith("BAT")) {
      continue;
    }

    Battery battery;
    if (scanBatteryItemSysfs(info.absoluteFilePath(), battery)) {
      list.append(battery);
    }
  }

  return true;
}

bool scanBatteryItemSysfs(const QString& dir_name, Battery& battery) {
  QDir dir(dir_name);
  if (!dir.exists()) {
    return false;
  }

  battery.technology = readTextFile(dir.filePath("technology")).trimmed();
  battery.manufacturer = readTextFile(dir.filePath("manufacturer")).trimmed();
  battery.model_name = readTextFile(dir.filePath("model_name")).trimmed();
  battery.status = readTextFile(dir.filePath("status")).trimmed();
  battery.capacity = readTextFile(dir.filePath("capacity")).trimmed().toInt();
  battery.capacity_level = readTextFile(dir.filePath("capacity_level")).trimmed();
  battery.serial_number = readTextFile(dir.filePath("serial_number")).trimmed();

  return true;
}

}  // namespace devices
}  // namespace sysinfo