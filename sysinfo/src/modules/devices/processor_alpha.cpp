// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/processor.h"

#include <QTextStream>

#include "base/file.h"

namespace sysinfo {
namespace devices {

bool getProcessorList(Processors& processors) {
  QString content;
  if (!readTextFile(kProcCpuInfo, content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  Processor processor;

  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    const QString& name = parts.at(0);
    const QString& value = parts.at(1);
    if (parts.length() == 2 && !name.isEmpty() && !value.isEmpty()) {
      if (name == "cpu model") {
        processor.model_name = QString("Alpha %1").arg(value);
      } else if (name == "platform string") {
        processor.str_model = value;
      } else if (name == "cycle frequency [Hz]") {
        const qint64 hz = value.toLongLong();
        processor.cpu_mhz = hz / 1000000.0;
      }
    }
  }

  processors.append(processor);
  return true;
}

}  // namespace devices
}  // namespace sysinfo