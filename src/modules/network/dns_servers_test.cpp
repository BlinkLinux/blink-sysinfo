// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include <gtest/gtest.h>

#include "modules/network/dns_servers.h"

namespace sysinfo {
namespace network {

TEST(DnsServerTest, TestGetServerList) {
  DnsServerList list;
  const bool ok = getDnsServers(list);
  ASSERT_TRUE(ok);
  ASSERT_GT(list.length(), 1);
}

TEST(DnsServerTest, TestGetHostnameByIp) {
  const QString hostname = getHostnameByIp("8.8.8.8");
  ASSERT_EQ(hostname, QString("dns.google"));
}

}  // namespace network
}  // namespace sysinfo