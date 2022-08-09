// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/audio_devices.h"

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool getAudioDevices(AudioDevices& list) {
  QString content;
  if (!readTextFile("/proc/asound/cards", content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  while (stream.readLineInto(&line)) {
    if (line.contains(':')) {
      const QStringList parts = line.split(':');
      list.append(parts.at(1).trimmed());
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo