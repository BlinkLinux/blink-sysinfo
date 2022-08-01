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

struct ProcessorFlag {
  QString name{};
  QString description{};
};

struct Processor {
  // processor id
  qint32 id{};
  qint32 physical_id{};
  qint32 cpu_cores{};
  qint32 core_id{};

  QString model_name{};
  QString vendor_id{};
  QVector<ProcessorFlag> flags{};

  QString power_management{};
  QString microcode{};
  QStringList bugs{};

  QString str_model{};
  qint64 cache_size{};
  qint32 model_id{};
  qint32 family_id{};
  qint32 stepping{};

  float cpu_mhz{};
  float bogomips{};

  bool has_fpu{};
  bool is_little_endian{};
};

using Processors = QVector<Processor>;

QJsonObject dump(const ProcessorFlag& flag);
QJsonObject dump(const Processor& processor);
QJsonArray dump(const Processors& processors);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_
