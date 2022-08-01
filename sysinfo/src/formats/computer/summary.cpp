// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/computer/summary.h"

namespace sysinfo {
namespace computer {

QJsonObject dump(const Summary& summary) {
  QJsonObject obj;
  obj.insert("processors", dump(summary.processors));
  obj.insert("board", dump(summary.board));
  obj.insert("audioDevices", QJsonArray::fromStringList(summary.audio_devices));
  return obj;
}

}  // namespace computer
}  // namespace sysinfo