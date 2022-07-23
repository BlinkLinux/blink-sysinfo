// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/main_controller.h"

namespace sysinfo {

MainController::MainController(QObject* parent) : QObject(parent) {

}

bool MainController::init() {
  return false;
}

}  // namespace sysinfo