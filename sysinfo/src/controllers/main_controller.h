// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_CONTROLLERS_MAIN_CONTROLLER_H_
#define SYSINFO_SRC_CONTROLLERS_MAIN_CONTROLLER_H_

#include <QObject>

namespace sysinfo {

class MainController : public QObject {
 Q_OBJECT
 public:
  explicit MainController(QObject* parent = nullptr);

  bool init();
};

}  // namespace sysinfo

#endif //SYSINFO_SRC_CONTROLLERS_MAIN_CONTROLLER_H_
