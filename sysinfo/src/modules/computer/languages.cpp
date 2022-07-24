// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/languages.h"

#include <QTextStream>

#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getLanguageList(LanguageList& list) {
  QString out;
  const bool ok = getCommandOutput("locale -va", out);
  if (!ok) {
    return false;
  }

  QString line;
  QTextStream stream(&out);
  LocaleInfo info{};
  while (stream.readLineInto(&line)) {
    if (line.isEmpty()) {
      // Next line is a new record.
      list.append(info);
      // Reset last record.
      info = LocaleInfo{};
      continue;
    }

    if (line.startsWith("locale:")) {
      const QStringList parts = line.split(" ");
      if (parts.length() > 1) {
        info.locale = parts.at(1);
      }
      continue;
    }

    if (line.startsWith("------")) {
      // detail part
      continue;
    }
    const QStringList parts = line.split('|');
    if (parts.length() != 2) {
      continue;
    }

    const QString& name = parts.at(0).trimmed();
    const QString value = parts.at(1).trimmed();
    if (name == "title") {
      info.title = value;
    } else if (name == "source") {
      info.source = value;
    } else if (name == "address") {
      info.address = value;
    } else if (name == "email") {
      info.email = value;
    } else if (name == "language") {
      info.language = value;
    } else if (name == "territory") {
      info.territory = value;
    } else if (name == "revision") {
      info.revision = value;
    } else if (name == "date") {
      info.date = value;
    } else if (name == "codeset") {
      info.codeset = value;
    }
  }
  list.append(info);

  return true;
}

}  // namespace computer
}  // namespace sysinfo