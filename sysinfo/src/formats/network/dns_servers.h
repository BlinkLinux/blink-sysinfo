// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef SYSINFO_SRC_FORMATS_NETWORK_DNS_SERVERS_H_
#define SYSINFO_SRC_FORMATS_NETWORK_DNS_SERVERS_H_

#include <QString>
#include <QVector>

namespace sysinfo {
namespace network {

struct DnsServer {
  QString ip{};
  QString hostname{};
};

using DnsServerList = QVector<DnsServer>;

}  // namespace network
}  // namespace sysinfo

#endif  // SYSINFO_SRC_FORMATS_NETWORK_DNS_SERVERS_H_