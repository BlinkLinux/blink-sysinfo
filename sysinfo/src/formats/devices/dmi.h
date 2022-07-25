// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_DMI_H_
#define SYSINFO_SRC_FORMATS_DEVICES_DMI_H_

#include <QString>

namespace sysinfo {
namespace devices {

struct DmiProduct {
  QString name{};
  QString family{};
  QString manufacturer{};
  QString vendor_name{};
  QString vendor_url{};
  QString version{};
};

struct DmiBios {
  QString release_date{};
  QString manufacturer{};
  QString vendor_name{};
  QString vendor_url{};
  QString version{};
};

struct DmiBoard {
  QString product_name{};
  QString manufacturer{};
  QString vendor_name{};
  QString vendor_url{};
  QString version{};
  QString serial_number{};
  QString asset_tag{};
};

struct DmiChassis {
  QString manufacturer{};
  QString vendor_name{};
  QString vendor_url{};
  QString type{};
  QString version{};
  QString serial_number{};
  QString asset_tag{};
};

struct Dmi {
  DmiProduct product{};
  DmiBios bios{};
  DmiBoard board{};
  DmiChassis chassis{};
};

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_DMI_H_
