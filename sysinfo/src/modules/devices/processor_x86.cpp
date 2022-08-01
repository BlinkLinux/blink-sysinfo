// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/processor_x86.h"

#include <QTextStream>

#include "base/file.h"
#include "base/unit.h"
#include "modules/devices/processor.h"

namespace sysinfo {
namespace devices {

// This function is partly based on x86cpucaps by Osamu Kayasono <jacobi@jcom.home.ne.jp>
QString getProcessorStringFamily(const QString& vendor_id, qint32 family, qint32 model) {
  if (vendor_id == "GenuineIntel") {
    if (family == 4) {
      return "i486 series";
    } else if (family == 5) {
      if (model < 4) {
        return "Pentium Classic";
      } else {
        return "Pentium MMX";
      }
    } else if (family == 6) {
      if (model <= 1) {
        return "Pentium Pro";
      } else if (model < 7) {
        return "Pentium II/Pentium II Xeon/Celeron";
      } else if (model == 9) {
        return "Pentium M";
      } else {
        return "Pentium III/Pentium III Xeon/Celeron/Core Duo/Core Duo 2";
      }
    } else if (family > 6) {
      return "Pentium 4";
    } else {
      return "i386 class";
    }
  } else if (vendor_id == "AuthenticAMD") {
    if (family == 4) {
      if (model <= 9) {
        return "AMD i80486 series";
      } else {
        return "AMD 5x86";
      }
    } else if (family == 5) {
      if (model <= 3) {
        return "AMD K5";
      } else if (model <= 7) {
        return "AMD K6";
      } else if (model == 8) {
        return "AMD K6-2";
      } else if (model == 9) {
        return "AMD K6-III";
      } else {
        return "AMD K6-2+/III+";
      }
    } else if (family == 6) {
      if (model == 1) {
        return "AMD Athlon (K7)";
      } else if (model == 2) {
        return "AMD Athlon (K75)";
      } else if (model == 3) {
        return "AMD Duron (Spitfire)";
      } else if (model == 4) {
        return "AMD Athlon (Thunderbird)";
      } else if (model == 6) {
        return "AMD Athlon XP/MP/4 (Palomino)";
      } else if (model == 7) {
        return "AMD Duron (Morgan)";
      } else if (model == 8) {
        return "AMD Athlon XP/MP (Thoroughbred)";
      } else if (model == 10) {
        return "AMD Athlon XP/MP (Barton)";
      } else {
        return "AMD Athlon (unknown)";
      }
    } else if (family > 6) {
      return "AMD Opteron/Athlon64/FX";
    } else {
      return "AMD i386 class";
    }
  } else if (vendor_id == "CyrixInstead") {
    if (family == 4) {
      return "Cyrix 5x86";
    } else if (family == 5) {
      return "Cyrix M1 (6x86)";
    } else if (family == 6) {
      if (model == 0) {
        return "Cyrix M2 (6x86MX)";
      } else if (model <= 5) {
        return "VIA Cyrix III (M2 core)";
      } else if (model == 6) {
        return "VIA Cyrix III (WinChip C5A)";
      } else if (model == 7) {
        return "VIA Cyrix III (WinChip C5B/C)";
      } else {
        return "VIA Cyrix III (WinChip C5C-T)";
      }
    } else {
      return "Cyrix i386 class";
    }
  } else if (vendor_id == "CentaurHauls") {
    if (family == 5) {
      if (model <= 4) {
        return "Centaur WinChip C6";
      } else if (model <= 8) {
        return "Centaur WinChip 2";
      } else {
        return "Centaur WinChip 2A";
      }
    } else {
      return "Centaur i386 class";
    }
  } else if (vendor_id == "GenuineTMx86") {
    return "Transmeta Crusoe TM3x00/5x00";
  }

  return "";
}

bool getProcessorList(Processors& processors) {
  QString content;
  if (!readTextFile(kProcCpuInfo, content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  Processor processor;
  bool processor_init = false;

  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    if (parts.length() != 2) {
      continue;
    }
    const QString name = parts.at(0).trimmed();
    const QString value = parts.at(1).trimmed();

    if (name.startsWith("processor")) {
      // finish previous
      if (processor_init) {
        processors.append(processor);
      }
      // start next
      processor = Processor{};
      processor.id = value.toInt();
      processor_init = true;
      continue;
    }

    if (name == "physical id") {
      processor.physical_id = value.toInt();
    } else if (name == "cpu cores") {
      processor.cpu_cores = value.toInt();
    } else if (name == "core id") {
      processor.core_id = value.toInt();

    } else if (name == "model name") {
      processor.model_name = value;
    } else if (name == "vendor_id") {
      processor.vendor_id = value;
    } else if (name == "flags") {
      const QStringList flags = value.split(' ');
      qDebug() << "flags:" << flags;

    } else if (name == "power management") {
      processor.power_management = value;
    } else if (name == "microcode") {
      processor.microcode = value;
    } else if (name == "bugs") {
      processor.bugs = value.split(' ');

    } else if (name == "cache size") {
      processor.cache_size = parseMemSize(value);
    } else if (name == "model") {
      processor.model_id = value.toInt();
    } else if (name == "cpu family") {
      processor.family_id = value.toInt();
    } else if (name == "stepping") {
      processor.stepping = value.toInt();

    } else if (name == "cpu MHz") {
      processor.cpu_mhz = value.toFloat();
    } else if (name == "bogomips") {
      processor.bogomips = value.toFloat();

    } else if (name == "fpu") {
      processor.has_fpu = true;
    }
  }

  processors.append(processor);

  return true;
}

}  // namespace devices
}  // namespace sysinfo