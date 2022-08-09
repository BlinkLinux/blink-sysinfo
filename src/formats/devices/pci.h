// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_DEVICES_PCI_H_
#define SYSINFO_SRC_FORMATS_DEVICES_PCI_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QStringList>

namespace sysinfo {
namespace devices {

struct PciDevMemory {
  qint64 start{};
  qint64 size{};
  bool is_64_bits{false};
  bool is_prefetchable{false};
};

struct PciDevIoPorts {
  qint64 start{};
  qint64 size{};
};

struct PciDev {
  // domain:bus.device.function
  QString id{};
  QString dev_class{};
  QString name{};
  QString subsystem{};

  QString vendor_name{};
  QString vendor_url{};
  QString oem_vendor_name{};
  QString oem_vendor_url{};

  PciDevIoPorts io_ports{};
  QStringList kernel_modules{};
  QVector<PciDevMemory> memories{};

  qint32 irq{};
  bool is_bus_master{};
};

using PciDevList = QVector<PciDev>;

QJsonObject dump(const PciDevMemory& memory);
QJsonObject dump(const PciDevIoPorts& io_port);
QJsonObject dump(const PciDev& dev);
QJsonArray dump(const PciDevList& list);

}  // namespace devices
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_DEVICES_PCI_H_
