// Copyright (c) 2021 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_BASE_PROCESS_H_
#define SYSINFO_SRC_BASE_PROCESS_H_

#include <QString>
#include <QStringList>

namespace sysinfo {

bool getCommandOutput(const QString& cmd, QString& output);
bool getCommandOutput(const QString& cmd, QString& output, QString& err);
bool getCommandOutputWithArgs(const QString& cmd, const QStringList& args, QString& output);
bool getCommandOutputWithArgs(const QString& cmd, const QStringList& args, QString& output, QString& err);

}  // namespace sysinfo

#endif  // SYSINFO_SRC_BASE_PROCESS_H_
