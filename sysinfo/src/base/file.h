// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_BASE_FILE_H_
#define SYSINFO_SRC_BASE_FILE_H_

#include <QString>

namespace sysinfo {

QByteArray readBinaryFile(const QString& path);

QString readTextFile(const QString& path);

bool readTextFile(const QString& path, QString& content);

bool writeBinaryFile(const QString& path, const QByteArray& bytes);


}  // namespace sysinfo

#endif //SYSINFO_SRC_BASE_FILE_H_
