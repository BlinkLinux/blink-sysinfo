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

struct ProcessorBug {
  QString name{};
  QString description{};
};

enum class ProcessorCacheType : quint8 {
  Data,
  Instruction,
  Unified,
};

struct ProcessorCache {
  qint64 size{};
  qint32 coherency_line_size{};
  qint32 id{};
  qint32 level{};
  qint32 number_of_sets{};
  qint32 physical_line_partition{};
  qint32 ways_of_associativity{};
  ProcessorCacheType type{};
};

using ProcessorCaches = QVector<ProcessorCache>;

struct ProcessorFrequency {
  qint32 base_freq_khz{};
  qint32 cpuinfo_max_freq_khz{};
  qint32 cpuinfo_min_freq_khz{};
  qint32 cpuinfo_transition_latency_ns{};

  QStringList scaling_available_governors{};
  QString scaling_governor{};
  QString scaling_driver{};
  qint32 scaling_cur_freq_khz{};
  qint32 scaling_max_freq_khz{};
  qint32 scaling_min_freq_khz{};
};

struct Processor {
  // processor id
  qint32 id{};
  qint32 physical_id{};
  qint32 cpu_cores{};
  qint32 core_id{};

  QString model_name{};
  QString vendor_id{};
  QString vendor_name{};
  QString vendor_url{};
  QVector<ProcessorFlag> flags{};

  QString power_management{};
  QString microcode{};
  QVector<ProcessorBug> bugs{};

  ProcessorCaches caches{};
  ProcessorFrequency frequency{};

  QString family_model{};
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
QJsonArray dump(const QVector<ProcessorFlag>& flags);
QJsonObject dump(const ProcessorBug& bug);
QJsonArray dump(const QVector<ProcessorBug>& bugs);
QString dump(ProcessorCacheType type);
ProcessorCacheType parse(const QString& s);
QJsonObject dump(const ProcessorCache& cache);
QJsonArray dump(const ProcessorCaches& caches);
QJsonObject dump(const ProcessorFrequency& frequency);
QJsonObject dump(const Processor& processor);
QJsonArray dump(const Processors& processors);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_PROCESSOR_H_
