// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/development.h"

#include <QDebug>
#include <QObject>
#include <QRegularExpression>

#include "base/process.h"

namespace sysinfo {
namespace computer {
namespace {

struct LanguageCmd {
  QString compiler_name;
  QString display_name;
  QString version_cmd;
  QString regex;
  bool stdout;
};

using LanguageCmdList = QVector<LanguageCmd>;

bool parseLanguageCmd(const LanguageCmdList& languages, DevItems& items) {
  QString out;
  QString err;
  for (const auto& detect: languages) {
    DevItem item{};
    item.name = detect.compiler_name;
    item.display_name = detect.display_name;
    if (getCommandOutput(detect.version_cmd, out, err)) {
      QRegularExpression pattern(detect.regex);
      const QRegularExpressionMatch match = pattern.match(detect.stdout ? out : err);
      if (match.hasMatch()) {
        item.version = match.captured(0);
      }
    }
    items.append(item);
  }

  return true;
}

}  // namespace

bool getDevelopmentEnv(Development& dev) {
  const LanguageCmdList scripting_languages = {
      {"gbr3", QObject::tr("Gambas3 (gbr3)"), "gbr3 --version", R"(\d+\.\d+\.\d+)", true},
      {"python", QObject::tr("Python"), "python -V", R"(\d+\.\d+\.\d+)", false},
      {"python2", QObject::tr("Python2"), "python2 -V", R"(\d+\.\d+\.\d+)", false},
      {"python3", QObject::tr("Python3"), "python3 -V", R"(\d+\.\d+\.\d+)", true},
      {"perl", QObject::tr("Perl"), "perl -v", R"(\d+\.\d+\.\d+)", true},
      {"perl6", QObject::tr("Perl6 (VM)"), "perl6 -v", "(?<=This is ).*", true},
      {"perl6_vm", QObject::tr("Perl6"), "perl6 -v", R"((?<=implementing Perl )\w*\.\w*)", true},
      {"php", QObject::tr("PHP"), "php --version", R"(\d+\.\d+\.\S+)", true},
      {"ruby", QObject::tr("Ruby"), "ruby --version", R"(\d+\.\d+\.\d+)", true},
      {"bash", QObject::tr("Bash"), "bash --version", R"(\d+\.\d+\.\S+)", true},
  };
  const LanguageCmdList compiler_languages = {
      {"gcc", QObject::tr("C (GCC)"), "gcc -v", R"(\d+\.\d+\.\d+)", false},
      {"clang", QObject::tr("C (Clang)"), "clang -v", R"(\d+\.\d+)", false},
      {"dmd", QObject::tr("D (dmd)"), "dmd --help", R"(\d+\.\d+)", true},
      {"gbc3", QObject::tr("Gambas3 (gbc3)"), "gbc3 --version", R"(\d+\.\d+\.\d+)", true},
      {"java", QObject::tr("Java"), "javac -version", R"(\d+\.\d+\.\d+)", false},
      {"csharp_old", QObject::tr("CSharp (Mono, old)"), "mcs --version", R"(\d+\.\d+\.\d+\.\d+)", true},
      {"csharp", QObject::tr("CSharp (Mono)"), "gmcs --version", R"(\d+\.\d+\.\d+\.\d+)", true},
      {"vala", QObject::tr("Vala"), "valac --version", R"(\d+\.\d+\.\d+)", true},
      {"haskell", QObject::tr("Haskell (GHC)"), "ghc -v", R"(\d+\.\d+\.\d+)", false},
      {"pascal", QObject::tr("FreePascal"), "fpc -iV", R"(\d+\.\d+\.?\d*)", true},
      {"go", QObject::tr("Go"), "go version", R"(\d+\.\d+\.?\d* )", true},
      {"rust", QObject::tr("Rust"), "rustc --version", R"(\d+\.\d+\.?\d* )", true},
  };
  const LanguageCmdList tools = {
      {"make", QObject::tr("make"), "make --version", R"(\d+\.\d+)", true},
      {"gdb", QObject::tr("GDB"), "gdb --version", "(?<=^GNU gdb ).*", true},
      {"strace", QObject::tr("strace"), "strace -V", R"(\d+\.\d+\.?\d*)", true},
      {"valgrind", QObject::tr("valgrind"), "valgrind --version", R"(\d+\.\d+\.\S+)", true},
      {"qmake", QObject::tr("QMake"), "qmake --version", R"(\d+\.\S+)", true},
      {"cmake", QObject::tr("CMake"), "cmake --version", R"(\d+\.\d+\.?\d*)", true},
      {"gambas3", QObject::tr("Gambas3 IDE"), "gambas3 --version", R"(\d+\.\d+\.\d+)", true},
  };

  bool ok = parseLanguageCmd(scripting_languages, dev.scripting);
  ok &= parseLanguageCmd(compiler_languages, dev.compilers);
  ok &= parseLanguageCmd(tools, dev.tools);
  return ok;
}

}  // namespace computer
}  // namespace sysinfo