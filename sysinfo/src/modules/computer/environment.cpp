// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/environment.h"

#include <QProcessEnvironment>

namespace sysinfo {
namespace computer {

Environment getEnvironment() {
  return QProcessEnvironment::systemEnvironment().toStringList();
}

}  // namespace computer
}  // namespace sysinfo