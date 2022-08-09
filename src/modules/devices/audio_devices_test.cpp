// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/devices/audio_devices.h"

namespace sysinfo {
namespace devices {

TEST(AudioDevicesTest, TestGetAudioDeviceList) {
  AudioDevices list;
  const bool ok = getAudioDevices(list);
  ASSERT_TRUE(ok);
  ASSERT_FALSE(list.isEmpty());
}

}  // namespace devices
}  // namespace sysinfo