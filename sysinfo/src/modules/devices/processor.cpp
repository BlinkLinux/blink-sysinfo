// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/processor.h"

#include <cstdint>

#include <QDir>
#include <QFileInfo>

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool isLittleEndian() {
  volatile uint32_t x = 0x01234567;
  return (*((uint8_t*)(&x))) == 0x67;
}

QString getCpuFilepath(const QString& filename, qint32 cpuid) {
  return QString("/sys/devices/system/cpu/cpu%1/%2").arg(cpuid).arg(filename);
}

bool getProcessorCache(qint32 cpuid, ProcessorCaches& caches) {
  const QString cache_dir_s = getCpuFilepath("cache", cpuid);
  QDir cache_dir(cache_dir_s);
  for (const auto& info : cache_dir.entryInfoList({"index*"}, QDir::Filter::Dirs)) {
    QDir index_dir(info.absoluteFilePath());
    ProcessorCache cache;
    auto read_int = [&](const QString& filename) -> qint32 {
      return readTextFile(index_dir.absoluteFilePath(filename)).toInt();
    };
    cache.coherency_line_size = read_int("coherency_line_size");
    cache.id = read_int("id");
    cache.level = read_int("level");
    cache.number_of_sets = read_int("number_of_sets");
    cache.physical_line_partition = read_int("physical_line_partition");
    cache.ways_of_associativity = read_int("ways_of_associativity");

    const QString type = readTextFile(index_dir.absoluteFilePath("type"));
    cache.type = parse(type);

    caches.append(cache);
  }
  return true;
}

bool getProcessorFrequency(qint32 cpuid, ProcessorFrequency& frequency) {
  const QString freq_dir_s = getCpuFilepath("cpufreq", cpuid);
  QDir freq_dir(freq_dir_s);
  auto read_int = [&](const QString& filename) -> qint32 {
    return readTextFile(freq_dir.absoluteFilePath(filename)).toInt();
  };
  frequency.base_freq_khz = read_int("base_frequency");
  frequency.cpuinfo_max_freq_khz = read_int("cpuinfo_max_freq");
  frequency.cpuinfo_min_freq_khz = read_int("cpuinfo_min_freq");
  frequency.cpuinfo_transition_latency_ns = read_int("cpuinfo_transition_latency");

  frequency.scaling_max_freq_khz = read_int("scaling_max_freq");
  frequency.scaling_min_freq_khz = read_int("scaling_min_freq");
  frequency.scaling_cur_freq_khz = read_int("scaling_cur_freq");

  frequency.scaling_driver = readTextFile(freq_dir.absoluteFilePath("scaling_driver")).trimmed();
  frequency.scaling_governor = readTextFile(freq_dir.absoluteFilePath("scaling_governor")).trimmed();
  const auto governors = readTextFile(freq_dir.absoluteFilePath("scaling_available_governors"));
  frequency.scaling_available_governors = governors.trimmed().split(' ');

  return true;
}

}  // namespace devices
}  // namespace sysinfo