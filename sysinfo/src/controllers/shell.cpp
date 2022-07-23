// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/shell.h"

#include <QCoreApplication>
#include <Logger.h>
#include <ConsoleAppender.h>

#include "controllers/main_controller.h"

namespace sysinfo {

int initShell(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("sysinfo");
  //QCoreApplication::setApplicationVersion(kVersionGui);
  cuteLogger->registerAppender(new ConsoleAppender);

  QScopedPointer<MainController> controller(new MainController());
  controller->init();

  return QCoreApplication::exec();
}

}  // namespace sysinfo