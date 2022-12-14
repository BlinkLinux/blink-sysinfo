// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_CONTROLLERS_SHELL_H_
#define SYSINFO_SRC_CONTROLLERS_SHELL_H_

#include <QJsonObject>

namespace sysinfo {

int initShell(int argc, char** argv);

void writeObjectToStdout(const QJsonObject& object);

void readCommandLine();

bool getAllSections(QJsonObject& object);

bool getSpecificSection(const QString& section, QJsonObject& object);

}  // namespace sysinfo

#endif //SYSINFO_SRC_CONTROLLERS_SHELL_H_
