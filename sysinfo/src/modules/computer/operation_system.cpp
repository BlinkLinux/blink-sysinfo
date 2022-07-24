// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "modules/computer/operation_system.h"

#include <pwd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QObject>

#include "base/file.h"
#include "base/process.h"

namespace sysinfo {
namespace computer {

bool getOperationSystem(OperationSystem& os) {
  os.distro = detectDistro();

  utsname name{};
  if (uname(&name) == -1) {
    qWarning() << "uname() returns error:" << strerror(errno);
    return false;
  }
  os.distro = detectDistro();
  os.kernel_version = name.version;
  os.kernel = QString("%1 %2 (%3").arg(name.sysname, name.release, name.machine);
  os.hostname = name.nodename;
  os.language = getLanguage();
  os.lang_codec = getLanguageCodec();
  os.homedir = QDir::homePath();
  {
    struct passwd* pwd = getpwuid(getuid());
    if (pwd != nullptr) {
      os.username = pwd->pw_name;
    }
    pwd = getpwuid(geteuid());
    if (pwd != nullptr) {
      os.real_user = pwd->pw_name;
    }
  }
  os.libc = getLibcVersion();

  os.load_avg = getLoadAverage();

  return true;
}

QString detectDistro() {
  static const struct {
    const char* file;
    const char* codename;
    const char* rename_to;
  } distro_db[] = {
#define DB_PREFIX "/etc/"
      {DB_PREFIX "arch-release", "arch", "Arch Linux"},
      {DB_PREFIX "fatdog-version", "fatdog"},
      {DB_PREFIX "debian_version", "deb"},
      {DB_PREFIX "slackware-version", "slk"},
      {DB_PREFIX "mandrake-release", "mdk"},
      {DB_PREFIX "mandriva-release", "mdv"},
      {DB_PREFIX "fedora-release", "fdra"},
      {DB_PREFIX "coas", "coas"},
      {DB_PREFIX "environment.corel", "corel"},
      {DB_PREFIX "gentoo-release", "gnt"},
      {DB_PREFIX "conectiva-release", "cnc"},
      {DB_PREFIX "versão-conectiva", "cnc"},
      {DB_PREFIX "turbolinux-release", "tl"},
      {DB_PREFIX "yellowdog-release", "yd"},
      {DB_PREFIX "sabayon-release", "sbn"},
      {DB_PREFIX "arch-release", "arch"},
      {DB_PREFIX "enlisy-release", "enlsy"},
      {DB_PREFIX "SuSE-release", "suse"},
      {DB_PREFIX "sun-release", "sun"},
      {DB_PREFIX "zenwalk-version", "zen"},
      {DB_PREFIX "DISTRO_SPECS", "ppy", "Puppy Linux"},
      {DB_PREFIX "puppyversion", "ppy", "Puppy Linux"},
      {DB_PREFIX "distro-release", "fl"},
      {DB_PREFIX "vine-release", "vine"},
      {DB_PREFIX "PartedMagic-version", "pmag"},
      // RedHat must be the *last* one to be checked, since
      // some distros (like Mandrake) includes a redhat-relase file too.
      {DB_PREFIX "redhat-release", "rh"},
#undef DB_PREFIX
      {nullptr, nullptr}
  };

  QString contents;
  if (getCommandOutputWithArgs("lsb_release", {"-d",}, contents)) {
    constexpr const char description[] = "Description:\t";
    if (contents.startsWith(description)) {
      return contents.mid(static_cast<int>(strlen(description))).trimmed();
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

  return {};
}

QString getLanguage() {
  const QLocale current = QLocale::system();
  return QLocale::languageToString(current.language());
}

QString getLanguageCodec() {
  constexpr const char* tab_lang_env[] = {"LANGUAGE", "LANG", "LC_ALL", "LC_MESSAGES"};
  const char* lc = setlocale(LC_ALL, nullptr);

  QString env{};
  for (const char* name: tab_lang_env) {
    env = qEnvironmentVariable(name);
    if (!env.isEmpty()) {
      break;
    }
  }

  if (!env.isEmpty()) {
    if (lc != nullptr) {
      return QString("%1 (%2)").arg(lc, env);
    } else {
      return env;
    }
  } else if (lc != nullptr) {
    return lc;
  }

  return {};
}

QString getLibcVersion() {
  constexpr const struct {
    const char* test_cmd;
    const char* match_str;
    const char* lib_name;
    bool try_ver_str;
    bool use_stderr;
  } libs[] = {
      { "ldd --version", "GLIBC", "GNU C Library", true, false},
      { "ldd --version", "GNU libc", "GNU C Library", true, false},
      { "ldconfig -V", "GLIBC", "GNU C Library", true, false},
      { "ldconfig -V", "GNU libc", "GNU C Library", true, false},
      { "ldconfig -v", "uClibc", "uClibc or uClibc-ng", false, false},
      { "diet", "diet version", "diet libc", true, true},
  };

  QString out;
  QString err;
  for (const auto& lib : libs) {
    const bool ok = getCommandOutput(lib.test_cmd, out, err);
    if (!ok) {
      continue;
    }

    const int out_line = out.indexOf("\n");
    const int err_line = err.indexOf("\n");
    const QString& out_ref = lib.use_stderr ? err.left(err_line) : out.left(out_line);

    if (!out_ref.contains(lib.match_str)) {
      continue;
    }

    if (lib.try_ver_str) {
      // skip the first word, likely "ldconfig" or name of utility
      const int ver_index = out_ref.indexOf(' ');
      if (ver_index) {
        return QString("%1 / %2").arg(lib.lib_name, out_ref.mid(ver_index + 1));
      }
    }

    return lib.lib_name;
  }

  return {};
}

QString detectKdeVersion() {
  const char *tmp = getenv("KDE_SESSION_VERSION");
  QString cmd;
  if (tmp && tmp[0] == '4') {
    cmd = "kwin --version";
  } else {
    cmd = "kcontrol --version";
  }

  QString out;
  const bool ok = getCommandOutput(cmd, out);
  if (!ok) {
    return {};
  }

  if (out.startsWith("KDE: ")) {
    return out.left(static_cast<int>(strlen("KDE: ")));
  }
  return {};
}

QString detectGnomeVersion() {
  QString out{};
  bool ok = getCommandOutput("gnome-shell --version", out);
  if (ok) {
    if (out.startsWith("GNOME Shell ")) {
      const QString gnome = out.left(static_cast<int>(strlen("GNOME Shell ")));
      return QString("GNOME %1").arg(gnome);
    }
  }

  ok = getCommandOutput("gnome-about --gnome-version", out);
  if (ok) {
    if (out.startsWith("Version: ")) {
      const QString gnome = out.left(static_cast<int>(strlen("Version: ")));
      return QString("GNOME %1").arg(gnome);
    }
  }

  return {};
}

QString detectWindowManager() {
  QString wm{};
  // TODO(Shaohua): get wm info.
  if (wm == "Xfwm4") {
    return "XFCE 4";
  }

  QString curr_desktop = qEnvironmentVariable("XDG_CURRENT_DESKTOP");
  if (!curr_desktop.isEmpty()) {
    QString desk_session = qEnvironmentVariable("DESKTOP_SESSION");

    if (!desk_session.isEmpty() && curr_desktop != desk_session)
      return desk_session;
  }

  return {};
}

QString desktopWithSessionType(const QString& desktop_env) {
  const QString value = qEnvironmentVariable("XDG_SESSION_TYPE");
  if (!value.isEmpty() && value != "unspecified") {
    // {desktop environment} on {session type}
    return QString("%1 on %2").arg(desktop_env, value);
  }

  return desktop_env;
}

QString detectXdgEnvironment(const char* env_var) {
  QString value = qEnvironmentVariable(env_var);
  if (value.isEmpty()) {
    return {};
  }

  if (value == "GNOME" || value == "gnome") {
    QString maybe_gnome = detectGnomeVersion();
    if (!maybe_gnome.isEmpty()) {
      return maybe_gnome;
    }
  }

  if (value == "KDE" || value == "kde") {
    QString maybe_kde = detectKdeVersion();
    if (!maybe_kde.isEmpty()) {
      return maybe_kde;
    }
  }

  return value;
}


QString detectDesktopEnvironment() {
  QString wm = detectXdgEnvironment("XDG_CURRENT_DESKTOP");
  if (!wm.isEmpty()) {
    return wm;
  }

  wm = detectXdgEnvironment("XDG_SESSION_DESKTOP");
  if (!wm.isEmpty()) {
    return wm;
  }

  QString value = qEnvironmentVariable("KDE_FULL_SESSION");
  if (!value.isEmpty()) {
    QString maybe_kde = detectKdeVersion();
    if (!maybe_kde.isEmpty()) {
      return maybe_kde;
    }
  }
  value = qEnvironmentVariable("GNOME_DESKTOP_SESSION_ID");
  if (!value.isEmpty()) {
    QString maybe_gnome = detectGnomeVersion();
    if (!maybe_gnome.isEmpty()) {
      return maybe_gnome;
    }
  }

  wm = detectWindowManager();
  if (!wm.isEmpty()) {
    return wm;
  }

  value = qEnvironmentVariable("DISPLAY");
  if (value.isEmpty()) {
    return QObject::tr("Terminal");
  }

  return {};
}

QStringList getLoadAverage() {
  QString content{};
  if (!readTextFile("/proc/loadavg", content)) {
    return {};
  }

  QStringList parts = content.split(' ');
  if (parts.length() < 3) {
    return parts;
  }
  return { parts.at(0), parts.at(1), parts.at(2) };
}

}  // namespace computer
}  // namespace sysinfo
