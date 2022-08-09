// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/shell.h"

#include <unistd.h>

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QJsonDocument>
#include <Logger.h>
#include <ConsoleAppender.h>

#include "config/config.h"
#include "modules/computer/computer.h"
#include "modules/devices/devices.h"
#include "modules/network/network.h"

namespace sysinfo {

void writeObjectToStdout(const QJsonObject& object) {
  QJsonDocument doc;
  doc.setObject(object);
  const QByteArray bytes = doc.toJson();
  const std::string s = bytes.toStdString();
  write(STDOUT_FILENO, s.c_str(), s.size());
}

bool getAllSections(QJsonObject& object) {
  computer::ComputerInfo computer_info;
  computer::getComputerInfo(computer_info);
  object.insert(computer::kNameComputer, dump(computer_info));

  devices::DevicesInfo devices_info;
  devices::getDevicesInfo(devices_info);
  object.insert(devices::kNameDevices, dump(devices_info));

  network::NetworkInfo network_info;
  network::getNetworkInfo(network_info);
  object.insert(network::kNameNetwork, dump(network_info));

  return true;
}

bool getSpecificSection(const QString& section, QJsonObject& object) {
  if (section == computer::kNameComputer) {
    computer::ComputerInfo info;
    computer::getComputerInfo(info);
    object = dump(info);
    return true;
  }

  if (section == devices::kNameDevices) {
    devices::DevicesInfo info;
    devices::getDevicesInfo(info);
    object = dump(info);
    return true;
  }

  if (section == network::kNameNetwork) {
    network::NetworkInfo info;
    network::getNetworkInfo(info);
    object = dump(info);
    return true;
  }

  const QStringList parts = section.split('.');
  if (parts.length() == 2) {
    const QString& parent = parts.at(0);
    const QString& child = parts.at(1);
    if (parent == computer::kNameComputer) {
      return computer::getSpecificSection(child, object);
    } else if (parent == devices::kNameDevices) {
      return devices::getSpecificSection(child, object);
    } else if (parent == network::kNameNetwork) {
      return network::getSpecificSection(child, object);
    }
  }
  qWarning() << "Invalid section:" << section;
  return false;
}

void readCommandLine() {
  QCommandLineParser parser;
  parser.addVersionOption();
  parser.addHelpOption();
  parser.addPositionalArgument("section",
                               "Fetch specific section, like 'computer' or 'computer.os'",
                               "[section]");
  parser.process(QCoreApplication::arguments());

  const QStringList sections = parser.positionalArguments();

  QJsonObject object;
  if (sections.isEmpty()) {
    getAllSections(object);
  } else {
    const QString& section = sections.first();
    if (!getSpecificSection(section, object)) {
      return;
    }
  }
  writeObjectToStdout(object);
}

int initShell(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("sysinfo");
  QCoreApplication::setApplicationVersion(kAppVersion);
  cuteLogger->registerAppender(new ConsoleAppender);

  readCommandLine();

  return 0;
}

}  // namespace sysinfo