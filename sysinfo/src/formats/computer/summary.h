// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_COMPUTER_SUMMARY_H_
#define SYSINFO_SRC_FORMATS_COMPUTER_SUMMARY_H_

#include <QJsonObject>
#include <QString>

#include "formats/devices/audio_devices.h"
#include "formats/devices/dmi.h"
#include "formats/devices/processor.h"

namespace sysinfo {
namespace computer {

struct Summary {
  devices::Processors processors{};
  devices::DmiBoard board{};
  // TODO(Shaohua): Add printers
  // TODO(Shaohua): Add storage
  devices::AudioDevices audio_devices{};
};

QJsonObject dump(const Summary& summary);

}  // namespace computer
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_COMPUTER_SUMMARY_H_
