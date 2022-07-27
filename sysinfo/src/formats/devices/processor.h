// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_
#define SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace devices {

struct Processor {
  QString vendor_id{};
  QString model_name{};
  qint32 model_id{};
  qint32 family_id{};
  QString str_model{};

  float cpu_mhz{};
  bool is_little_endian{};
};

using Processors = QVector<Processor>;

QJsonObject dump(const Processor& processor);
QJsonArray dump(const Processors& processors);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_
