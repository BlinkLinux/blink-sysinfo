// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/processor.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const ProcessorFlag& flag) {
  QJsonObject obj;
  obj.insert("name", flag.name);
  obj.insert("description", flag.description);
  return obj;
}

QJsonArray dump(const QVector<ProcessorFlag>& flags) {
  QJsonArray array;
  for (const auto& flag : flags) {
    array.append(dump(flag));
  }
  return array;
}

QJsonObject dump(const ProcessorBug& bug) {
  QJsonObject obj;
  obj.insert("name", bug.name);
  obj.insert("description", bug.description);
  return obj;
}

QJsonArray dump(const QVector<ProcessorBug>& bugs) {
  QJsonArray array;
  for (const auto& bug : bugs) {
    array.append(dump(bug));
  }
  return array;
}

QString dump(ProcessorCacheType type) {
  switch (type) {
    case ProcessorCacheType::Data: {
      return "data";
    }
    case ProcessorCacheType::Instruction: {
      return "instruction";
    }
    case ProcessorCacheType::Unified: {
      return "unified";
    }
    default: {
      return {};
    }
  }
}

QJsonObject dump(const ProcessorCache& cache) {
  QJsonObject obj;
  obj.insert("size", cache.size);
  obj.insert("coherencyLineSize", cache.coherency_line_size);
  obj.insert("id", cache.id);
  obj.insert("level", cache.level);
  obj.insert("numberOfSets", cache.number_of_sets);
  obj.insert("physicalLinePartition", cache.physical_line_partition);
  obj.insert("waysOfAssociativity", cache.ways_of_associativity);
  QJsonArray list;
  for (const auto& cpu : cache.shared_cpu_list) {
    list.append(QJsonValue::fromVariant(cpu));
  }
  obj.insert("sharedCpu", list);
  obj.insert("type", dump(cache.type));
  return obj;
}

QJsonArray dump(const QVector<ProcessorCache>& caches) {
  QJsonArray array;
  for (const auto& cache : caches) {
    array.append(dump(cache));
  }
  return array;
}

QJsonObject dump(const Processor& processor) {
  QJsonObject obj;
  obj.insert("id", processor.id);
  obj.insert("physicalId", processor.physical_id);
  obj.insert("cpuCores", processor.cpu_cores);
  obj.insert("coreId", processor.core_id);

  obj.insert("modelName", processor.model_name);
  obj.insert("vendorId", processor.vendor_id);
  obj.insert("flags", dump(processor.flags));

  obj.insert("powerManagement", processor.power_management);
  obj.insert("microcode", processor.microcode);
  obj.insert("bugs", dump(processor.bugs));

  obj.insert("familyModel", processor.family_model);
  obj.insert("cacheSize", processor.cache_size);
  obj.insert("modelId", processor.model_id);
  obj.insert("familyId", processor.family_id);
  obj.insert("stepping", processor.stepping);

  obj.insert("cpuMhz", processor.cpu_mhz);
  obj.insert("bogomips", processor.bogomips);

  obj.insert("hasFpu", processor.has_fpu);
  obj.insert("isLittleEndian", processor.is_little_endian);

  return obj;
}

QJsonArray dump(const Processors& processors) {
  QJsonArray array;
  for (const auto& p : processors) {
    array.append(dump(p));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo