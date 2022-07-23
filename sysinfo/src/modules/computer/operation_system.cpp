// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "modules/computer/operation_system.h"

#include <sys/utsname.h>

#include <QDebug>
#include <QObject>

#include "base/file.h"
#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getOperationSystem(OperationSystem& os) {
  utsname name;
  if (uname(&name) == -1) {
    qWarning() << "uname() returns error:" << strerror(errno);
    return false;
  }
  os.distro = detectDistro();
  os.kernel_version = name.version;
  os.kernel = QString("%1 %2 (%3").arg(name.sysname, name.release, name.machine);
  os.hostname = name.nodename;

  return false;
}

QString detectDistro() {
  static const struct {
    const char* file;
    const char* codename;
    const char* rename_to;
  } distro_db[] = {
#define DB_PREFIX "/etc/"
    { DB_PREFIX "arch-release", "arch", "Arch Linux" },
    { DB_PREFIX "fatdog-version", "fatdog" },
    { DB_PREFIX "debian_version", "deb" },
    { DB_PREFIX "slackware-version", "slk" },
    { DB_PREFIX "mandrake-release", "mdk" },
    { DB_PREFIX "mandriva-release", "mdv" },
    { DB_PREFIX "fedora-release", "fdra" },
    { DB_PREFIX "coas", "coas" },
    { DB_PREFIX "environment.corel", "corel"},
    { DB_PREFIX "gentoo-release", "gnt" },
    { DB_PREFIX "conectiva-release", "cnc" },
    { DB_PREFIX "versão-conectiva", "cnc" },
    { DB_PREFIX "turbolinux-release", "tl" },
    { DB_PREFIX "yellowdog-release", "yd" },
    { DB_PREFIX "sabayon-release", "sbn" },
    { DB_PREFIX "arch-release", "arch" },
    { DB_PREFIX "enlisy-release", "enlsy" },
    { DB_PREFIX "SuSE-release", "suse" },
    { DB_PREFIX "sun-release", "sun" },
    { DB_PREFIX "zenwalk-version", "zen" },
    { DB_PREFIX "DISTRO_SPECS", "ppy", "Puppy Linux" },
    { DB_PREFIX "puppyversion", "ppy", "Puppy Linux" },
    { DB_PREFIX "distro-release", "fl" },
    { DB_PREFIX "vine-release", "vine" },
    { DB_PREFIX "PartedMagic-version", "pmag" },
    // RedHat must be the *last* one to be checked, since
    // some distros (like Mandrake) includes a redhat-relase file too.
    { DB_PREFIX "redhat-release", "rh" },
#undef DB_PREFIX
    { nullptr, nullptr }
  };

  QString contents;
  if (getCommandOutput("lsb_release", { "-d", }, contents)) {
    constexpr const char description[] = "Description:\t";
    if (contents.startsWith(description)) {
//      return contents.mid(static_cast<int>(strlen(description))).trimmed();
    }
  }

  for (int i = 0; distro_db[i].file; i++) {
    if (!readTextFile(distro_db[i].file, contents)) {
      continue;
    }
    contents = contents.trimmed();

    if (distro_db[i].rename_to != nullptr) {
      return distro_db[i].rename_to;
    }

    if (strncmp(distro_db[i].codename, "deb", 3) == 0) {
        // HACK: Some Debian systems doesn't include the distribution
        // name in /etc/debian_release, so add them here.
        if (contents.at(0).isDigit() || contents.at(0) != 'D') {
          return QString("Debian GNU/Linux %1").arg(contents);
        }
    }

    if (strncmp(distro_db[i].codename, "fatdog", 6) == 0) {
      return QString("Fatdog64 [%1]").arg(contents);
    }

    return contents;
  }

  return QObject::tr("Unknown");
}

}  // namespace computer
}  // namespace sysinfo
