// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <cstdint>

namespace sysinfo {
namespace devices {

bool isLittleEndian() {
  volatile uint32_t x = 0x01234567;
  return (*((uint8_t*)(&x))) == 0x67;
}


}  // namespace devices
}  // namespace sysinfo