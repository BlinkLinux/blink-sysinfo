// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_OPERATION_SYSTEM_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_OPERATION_SYSTEM_H_

#include <QJsonObject>
#include <QString>
#include <QStringList>

namespace sysinfo {
namespace computer {

struct OperationSystem {
  QString distro{};
  QString kernel_version{};
  QString kernel{};
  QString hostname{};
  QString language{};
  QString lang_codec{};
  QString home{};
  QString username{};
  QString real_user{};
  QString libc{};
  QString desktop{};
  QVector<double> load_avg{};
};

QJsonObject dump(const OperationSystem& os);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_OPERATION_SYSTEM_H_
