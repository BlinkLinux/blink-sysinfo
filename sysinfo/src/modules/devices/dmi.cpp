// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/dmi.h"

#include <QDir>
#include <QFileInfo>
#include <QStringList>

#include "base/file.h"
#include "modules/shared/vendor.h"

namespace sysinfo {
namespace devices {

QString dmiGetSysfsRoot() {
  const QStringList list = {
      "/sys/devices/virtual/dmi",
      "/sys/class/dmi",
  };
  for (const auto& file : list) {
    if (QFileInfo::exists(file)) {
      return file;
    }
  }
  return {};
}

bool getDmiInfo(Dmi& dmi) {
  const QString dir = dmiGetSysfsRoot();
  if (dir.isEmpty()) {
    return false;
  }

  const auto read_file = [&dir](const QString& filename) {
    const QString filepath = QDir(dir).filePath(filename);
    return readTextFile(filepath);
  };

  dmi.product.name = read_file("id/product_name");
  dmi.product.family = read_file("id/product_family");
  dmi.product.version = read_file("id/product_version");
  dmi.product.manufacturer = read_file("id/sys_vendor");
  dmi.product.vendor_name = getVendorName(dmi.product.manufacturer);
  dmi.product.vendor_url = getVendorUrl(dmi.product.manufacturer);

  dmi.bios.release_date = read_file("id/bios_date");
  dmi.bios.manufacturer = read_file("id/bios_vendor");
  dmi.bios.vendor_name = getVendorName(dmi.bios.manufacturer);
  dmi.bios.vendor_url = getVendorUrl(dmi.bios.manufacturer);
  dmi.bios.version = read_file("id/bios_version");

  dmi.board.product_name = read_file("id/board_name");
  dmi.board.manufacturer = read_file("id/board_vendor");
  dmi.board.vendor_name = getVendorName(dmi.board.manufacturer);
  dmi.board.vendor_url = getVendorUrl(dmi.board.manufacturer);
  dmi.board.version = read_file("id/board_version");
  dmi.board.serial_number = read_file("id/board_serial");
  dmi.board.asset_tag = read_file("id/board_asset_tag");

  dmi.chassis.type = read_file("id/chassis_type");
  dmi.chassis.serial_number = read_file("id/chassis_serial");
  dmi.chassis.manufacturer = read_file("id/chassis_vendor");
  dmi.chassis.vendor_name = getVendorName(dmi.chassis.manufacturer);
  dmi.chassis.vendor_url = getVendorUrl(dmi.chassis.manufacturer);
  dmi.chassis.version = read_file("id/chassis_version");
  dmi.chassis.asset_tag = read_file("id/chassis_asset_tag");

  return true;
}

}  // namespace devices
}  // namespace sysinfo