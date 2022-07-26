// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_USB_H_
#define SYSINFO_SRC_FORMATS_DEVICES_USB_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

namespace sysinfo {
namespace devices {

struct UsbDev {
  QString id{};
  QString bus_id{};
  QString device_id{};
  QString name{};

  QString usb_version{};

  QString id_vendor{};
  QString id_vendor_name{};
  QString id_product{};
  QString id_product_name{};
  QString id_manufacturer{};

  QString max_power{};

  bool is_serial{};
};

using UsbDevList = QVector<UsbDev>;

QJsonObject dump(const UsbDev& dev);
QJsonArray dump(const UsbDevList& list);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_USB_H_
