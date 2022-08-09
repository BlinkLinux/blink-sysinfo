// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/dmi.h"

namespace sysinfo {
namespace devices {

QJsonObject dump(const DmiProduct& product) {
  QJsonObject obj;
  obj.insert("name", product.name);
  obj.insert("family", product.family);
  obj.insert("manufacturer", product.manufacturer);
  obj.insert("vendorName", product.vendor_name);
  obj.insert("vendorUrl", product.vendor_url);
  obj.insert("version", product.version);
  return obj;
}

QJsonObject dump(const DmiBios& bios) {
  QJsonObject obj;
  obj.insert("releaseDate", bios.release_date);
  obj.insert("manufacturer", bios.manufacturer);
  obj.insert("vendorName", bios.vendor_name);
  obj.insert("vendorUrl", bios.vendor_url);
  obj.insert("version", bios.version);
  return obj;
}

QJsonObject dump(const DmiBoard& board) {
  QJsonObject obj;
  obj.insert("productName", board.product_name);
  obj.insert("manufacturer", board.manufacturer);
  obj.insert("vendorName", board.vendor_name);
  obj.insert("vendorUrl", board.vendor_url);
  obj.insert("version", board.version);
  obj.insert("serialNumber", board.serial_number);
  obj.insert("assetTag", board.asset_tag);
  return obj;
}

QJsonObject dump(const DmiChassis& chassis) {
  QJsonObject obj;
  obj.insert("manufacturer", chassis.manufacturer);
  obj.insert("vendorName", chassis.vendor_name);
  obj.insert("vendorUrl", chassis.vendor_url);
  obj.insert("type", chassis.type);
  obj.insert("version", chassis.version);
  obj.insert("serialNumber", chassis.serial_number);
  obj.insert("assetTag", chassis.asset_tag);
  return obj;
}

QJsonObject dump(const Dmi& dmi) {
  QJsonObject obj;
  obj.insert("product", dump(dmi.product));
  obj.insert("bios", dump(dmi.bios));
  obj.insert("board", dump(dmi.board));
  obj.insert("chassis", dump(dmi.chassis));
  return obj;
}

}  // namespace devices
}  // namespace sysinfo