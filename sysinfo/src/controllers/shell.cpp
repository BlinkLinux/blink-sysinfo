// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/shell.h"

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <Logger.h>
#include <ConsoleAppender.h>

#include "config/config.h"
#include "modules/computer/computer.h"

namespace sysinfo {
namespace {

void readCommandLine() {
  QCommandLineParser parser;
  parser.addVersionOption();
  parser.addHelpOption();
  QCommandLineOption computer_opt("computer", "Fetch computer info");
  parser.addOption(computer_opt);
  QCommandLineOption devices_opt("devices", "Fetch hardware devices info");
  parser.addOption(devices_opt);
  QCommandLineOption network_opt("network", "Fetch network related info");
  parser.addOption(network_opt);

  parser.process(QCoreApplication::arguments());

  if (parser.isSet(computer_opt)) {
    computer::ComputerInfo info;
    const bool ok = computer::getComputerInfo(info);
    const QByteArray bytes = computer::dumpToJson(info);
    printf("%s", bytes.toStdString().c_str());
    return;
  }
  if (parser.isSet(devices_opt)) {
    return;
  }
  if (parser.isSet(network_opt)) {
    return;
  }
}

}  // namespace

int initShell(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("sysinfo");
  QCoreApplication::setApplicationVersion(kAppVersion);
  cuteLogger->registerAppender(new ConsoleAppender);

  readCommandLine();

  return 0;
}

}  // namespace sysinfo