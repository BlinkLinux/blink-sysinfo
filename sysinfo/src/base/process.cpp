// Copyright (c) 2021 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "base/process.h"

#include <QDebug>
#include <QProcess>

namespace sysinfo {

bool getCommandOutput(const QString& cmd, QString& output) {
  QString err{};
  return getCommandOutput(cmd, output, err);
}

bool getCommandOutput(const QString& cmd, QString& output, QString& err) {
  QProcess process;
  process.setProgram("sh");
  process.setArguments({
    "-c",
    cmd,
  });
  process.start();
  process.waitForFinished();
  const bool ok = (process.exitStatus() == QProcess::ExitStatus::NormalExit && process.exitCode() == 0);
  output = process.readAllStandardOutput();
  err = process.readAllStandardError();
  return ok;
}

bool getCommandOutputWithArgs(const QString& cmd, const QStringList& args, QString& output) {
  QString err;
  return getCommandOutputWithArgs(cmd, args, output, err);
}

bool getCommandOutputWithArgs(const QString& cmd, const QStringList& args, QString& output, QString& err) {
  QProcess process;
  process.setProgram(cmd);
  process.setArguments(args);
  process.start();
  process.waitForFinished();
  const bool ok = (process.exitStatus() == QProcess::ExitStatus::NormalExit && process.exitCode() == 0);
  output = process.readAllStandardOutput();
  err = process.readAllStandardError();
  return ok;
}

}  // namespace sysinfo