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
  // processor id
  qint32 id{};
  QString model_name{};
  QString vendor_id{};
  QString flags{};

  QString power_management{};
  QString microcode{};
  QString bugs{};
  QString fdiv_bug{};
  QString hlt_bug{};
  QString f00f_bug{};
  QString coma_bug{};

  QString str_model{};
  qint32 cache_size{};
  qint32 model_id{};
  qint32 family_id{};
  qint32 stepping{};

  float cpu_mhz{};
  float bogomips{};

  bool has_fpu{};
  bool is_little_endian{};
};

using Processors = QVector<Processor>;

QJsonObject dump(const Processor& processor);
QJsonArray dump(const Processors& processors);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_
