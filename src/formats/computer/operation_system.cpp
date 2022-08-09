// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "formats/computer/operation_system.h"

#include <QJsonArray>

namespace sysinfo {
namespace computer {

QJsonObject dump(const OperationSystem& os) {
  QJsonObject obj;
  obj.insert("distro", os.distro);
  obj.insert("kernelVersion", os.kernel_version);
  obj.insert("kernel", os.kernel);
  obj.insert("hostname", os.hostname);
  obj.insert("language", os.language);
  obj.insert("langCodec", os.lang_codec);
  obj.insert("home", os.home);
  obj.insert("username", os.username);
  obj.insert("realUser", os.real_user);
  obj.insert("libc", os.libc);
  obj.insert("desktop", os.desktop);
  QJsonArray load_avg;
  for (const auto value : os.load_avg) {
    load_avg.append(value);
  }
  obj.insert("loadingAverage", load_avg);
  return obj;
}

}  // namespace computer
}  // namespace sysinfo