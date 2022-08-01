// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/processor.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const Processor& processor) {
  QJsonObject obj;
  obj.insert("id", processor.id);
  obj.insert("modelName", processor.model_name);
  obj.insert("vendorId", processor.vendor_id);
  obj.insert("flags", processor.flags);

  obj.insert("cacheSize", processor.cache_size);
  obj.insert("modelId", processor.model_id);
  obj.insert("familyId", processor.family_id);

  obj.insert("cpuMhz", processor.cpu_mhz);

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