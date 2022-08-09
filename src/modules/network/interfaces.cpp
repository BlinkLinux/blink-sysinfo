// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/network/interfaces.h"

#include <arpa/inet.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

#include "base/file.h"

namespace sysinfo {
namespace network {
namespace {

}  // namespace

bool getNetworkInterfaces(NetworkInterfaceList& list) {
  QString content;
  if (!readTextFile("/proc/net/dev", content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  QRegularExpression space_pattern("\\s+");

  while (stream.readLineInto(&line)) {
    if (line.contains('|')) {
      continue;
    }

    const QStringList parts = line.trimmed().split(space_pattern);
    if (parts.length() < 4) {
      continue;
    }
    NetworkInterface iface{};
    iface.interface = parts.at(0).trimmed().remove(':');
    iface.received = parts.at(1).toLong();
    iface.sent = parts.at(2).toLong();
    iface.type = getIfaceType(iface.interface);
    if (getNetInfo(iface)) {
      list.append(iface);
    }
  }

  return true;
}

bool getNetInfo(NetworkInterface& iface) {
  const char* if_name = iface.interface.toStdString().c_str();
  struct ifreq ifr{};
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  /* IPv4 */
  ifr.ifr_addr.sa_family = AF_INET;

  /* MTU */
  strcpy(ifr.ifr_name, if_name);
  if (ioctl(fd, SIOCGIFMTU, &ifr) >= 0) {
    iface.mtu = ifr.ifr_mtu;
  }

  /* HW Address */
  strcpy(ifr.ifr_name, if_name);
  if (ioctl(fd, SIOCGIFHWADDR, &ifr) >= 0) {
    unsigned char mac[8];
    memcpy(mac, ifr.ifr_ifru.ifru_hwaddr.sa_data, 8);
    iface.mac = QString::asprintf("%02x:%02x:%02x:%02x:%02x:%02x",
                                  mac[0], mac[1], mac[2],
                                  mac[3], mac[4], mac[5]);
  }

  /* IP Address */
  strcpy(ifr.ifr_name, if_name);
  if (ioctl(fd, SIOCGIFADDR, &ifr) >= 0) {
    iface.ip = inet_ntoa(((struct sockaddr_in*) &ifr.ifr_addr)->sin_addr);
  }

  /* Mask Address */
  strcpy(ifr.ifr_name, if_name);
  if (ioctl(fd, SIOCGIFNETMASK, &ifr) >= 0) {
    iface.mask = inet_ntoa(((struct sockaddr_in*) &ifr.ifr_addr)->sin_addr);
  }

  /* Broadcast Address */
  strcpy(ifr.ifr_name, if_name);
  if (ioctl(fd, SIOCGIFBRDADDR, &ifr) >= 0) {
    iface.broadcast = inet_ntoa(((struct sockaddr_in*) &ifr.ifr_addr)->sin_addr);
  }

  shutdown(fd, 0);
  close(fd);

  return true;
}

NetworkInterfaceType getIfaceType(const QString& name) {
  struct NamePair {
    const char* prefix{};
    NetworkInterfaceType type{};
  };

//  { "plip", NC_("net-if-type", "Parallel Line Internet Protocol"), "network" },
//  { "irlan", NC_("net-if-type", "Infrared"), "network" },
//  { "slip", NC_("net-if-type", "Serial Line Internet Protocol"), "network" },
//  { "isdn", NC_("net-if-type", "Integrated Services Digital Network"), "modem" },
//  { "sit", NC_("net-if-type", "IPv6-over-IPv4 Tunnel"), "network" },
//  { "pan", NC_("net-if-type", "Personal Area Network (PAN)"), "bluetooth" },
//  { "ifb", NC_("net-if-type", "Intermediate Functional Block"), "network" },
//  { "gre", NC_("net-if-type", "GRE Network Tunnel"), "network" },
//  { "sl", NC_("net-if-type", "Serial Line Internet Protocol"), "network" },

  constexpr const NamePair kEthNames[] = {
      // ethernet
      {"eth", NetworkInterfaceType::Ethernet},
      {"tap", NetworkInterfaceType::Ethernet},
      {"en", NetworkInterfaceType::Ethernet},
      {"net", NetworkInterfaceType::Ethernet},

      {"lo", NetworkInterfaceType::Loopback},

      // wireless
      {"ath", NetworkInterfaceType::Wireless},
      {"wlan", NetworkInterfaceType::Wireless},
      {"ra", NetworkInterfaceType::Wireless},
      {"wmaster", NetworkInterfaceType::Wireless},
      {"wl", NetworkInterfaceType::Wireless},
      {"ww", NetworkInterfaceType::Wireless},

      // bridget
      {"br", NetworkInterfaceType::Bridge},
      {"docker", NetworkInterfaceType::Bridge},

      // p2p
      {"ppp", NetworkInterfaceType::PointToPoint},
      {"tun", NetworkInterfaceType::PointToPoint},

      // bluetooth
      {"bnep", NetworkInterfaceType::Bluetooth},

      // virtual
      {"vmnet8", NetworkInterfaceType::VirtualNetwork},
      {"vmnet", NetworkInterfaceType::VirtualNetwork},
      {"vboxnet", NetworkInterfaceType::VirtualNetwork},
      {"ham", NetworkInterfaceType::VirtualNetwork},
      {"veth", NetworkInterfaceType::VirtualNetwork},

      // mesh
      {"msh", NetworkInterfaceType::Mesh},
  };

  for (const auto& item: kEthNames) {
    if (name.startsWith(item.prefix)) {
      return item.type;
    }
  }

  return NetworkInterfaceType::Unknown;
}

}  // namespace network
}  // namespace sysinfo