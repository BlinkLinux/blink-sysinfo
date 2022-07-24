// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_MEMORY_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_MEMORY_H_

#include <QtGlobal>

namespace sysinfo {
namespace computer {

struct Memory {
  qint64 total{};
  qint64 free{};
  qint64 cached{};
};

}  // namespace computer
}  // namespace sysinfo

#endif //SYSINFO_SRC_FORMATS_COMPUTER_MEMORY_H_
