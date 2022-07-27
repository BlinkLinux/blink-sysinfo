// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/computer/summary.h"

#include "modules/devices/audio_devices.h"
#include "modules/devices/dmi.h"
#include "modules/devices/processor.h"

namespace sysinfo {
namespace computer {

bool getSummary(Summary& summary) {
  bool ok = true;
  ok &= devices::getAudioDevices(summary.audio_devices);
  ok &= devices::getProcessorList(summary.processors);
  devices::Dmi dmi;
  ok &= devices::getDmiInfo(dmi);
  summary.board = dmi.board;
  return ok;
}

}  // namespace computer
}  // namespace sysinfo