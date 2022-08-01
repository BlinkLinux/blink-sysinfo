// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/processor.h"

#include <cstdint>

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool isLittleEndian() {
  volatile uint32_t x = 0x01234567;
  return (*((uint8_t*)(&x))) == 0x67;
}

QString getCpuString(const QString& filename, qint32 cpuid) {
  const QString filepath = QString("/sys/devices/system/cpu/cpu%1/%2").arg(cpuid).arg(filename);
  return readTextFile(filepath);
}

qint32 getCpuInteger(const QString& file, qint32 cpuid) {
  return getCpuString(file, cpuid).toInt();
}

}  // namespace devices
}  // namespace sysinfo