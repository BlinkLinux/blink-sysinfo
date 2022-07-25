// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/modules.h"

#include <QRegularExpression>
#include <QTextStream>

#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getKernelModules(ModuleList& list) {
  QString out;
  if (!getCommandOutput("lsmod", out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line;
  // Ignore header line.
  stream.readLineInto(&line);
  QRegularExpression pattern("\\s+");
  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(pattern);
    Module module{};
    if (parts.length() > 1) {
      module.name = parts.at(0);
      module.memory_bytes = parts.at(1).toInt();

      if (getModuleDetail(module)) {
        list.append(module);
      }
    }
  }

  return true;
}

bool getModuleDetail(Module& module) {
  QString out;
  // TODO(Shaohua): Check modinfo command exists.
  if (!getCommandOutputWithArgs("/sbin/modinfo", {module.name}, out)) {
    return false;
  }

  QTextStream stream(&out);
  QString line;
  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    if (parts.length() < 2) {
      continue;
    }
    const QString& name = parts.at(0);
    const QString value = parts.at(1).trimmed();
    if (name == "filename") {
      module.path = value;
    } else if (name == "license") {
      module.license = value;
    } else if (name == "description") {
      module.description = value;
    } else if (name == "author") {
      module.author = value;
    } else if (name == "depends") {
      module.dependencies = value.split(',');
    } else if (name == "vermagic") {
      module.version_magic = value;
    } else if (name == "signer") {
      module.signer = value;
    } else if (name == "sig_key") {
      module.sig_key = value;
    }
  }

  return true;
}

}  // namespace computer
}  // namespace sysinfo