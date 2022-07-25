// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_ARP_TABLE_H_
#define SYSINFO_SRC_FORMATS_NETWORK_ARP_TABLE_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace network {

struct Arp {
  QString ip{};
  QString mac{};
  QString device{};
  qint32 hw_type{};
  qint32 flags{};
};

using ArpList = QVector<Arp>;

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_ARP_TABLE_H_
