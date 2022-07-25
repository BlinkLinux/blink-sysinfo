// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_MODULES_DEVICES_USB_H_
#define SYSINFO_SRC_MODULES_DEVICES_USB_H_

#include "formats/devices/usb.h"

namespace sysinfo {
namespace devices {

bool getUsbDevices(UsbDevList& list);

bool scanUsbLsusb(UsbDevList& list);

bool scanUsbLsusb(UsbDev& dev);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_MODULES_DEVICES_USB_H_
