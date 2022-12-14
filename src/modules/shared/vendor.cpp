// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/shared/vendor.h"

namespace sysinfo {
namespace {

struct Vendor {
  const char* id;
  const char* name;
  const char* url;
};

constexpr const Vendor kVendorList[] = {
    {"ATI", "ATI Technologies", "www.ati.com"},
    {"nVidia", "nVidia", "www.nvidia.com"},
    {"NVidia", "nVidia", "www.nvidia.com"},
    {"3Com", "3Com", "www.3com.com"},
    {"Intel", "Intel", "www.intel.com"},
    {"Cirrus Logic", "Cirrus Logic", "www.cirrus.com"},
    {"VIA Technologies", "VIA Technologies", "www.via.com.tw"},
    {"VIA", "VIA Technologies", "www.via.com.tw"},
    {"hp", "Hewlett-Packard", "www.hp.com"},
    {"NEC Corporation", "NEC Coporation", "www.nec.com"},
    {"MAXTOR", "MAXTOR", "www.maxtor.com"},
    {"SAMSUNG", "SAMSUNG", "www.samsung.com"},
    {"PIONEER", "PIONEER", "www.pioneer-eur.com"},
    {"PLEXTOR", "PLEXTOR", "www.plextor.be"},
    {"Realtek Semiconductor", "Realtek", "www.realtek.com.tw"},
    {"TOSHIBA", "TOSHIBA", "www.toshiba.com"},
    {"LITE-ON", "LITE-ON", "www.liteonit.com"},
    {"WDC", "Western Digital", "www.wdc.com"},
    {"HL-DT-ST", "LG Electronics", "www.lge.com"},
    {"ST", "SEAGATE", "www.seagate.com"},
    {"Lexmark", "Lexmark", "www.lexmark.com"},
    {"_NEC", "NEC Corporation", "www.nec.com"},
    {"Creative Labs", "Creative Labs", "www.creative.com"},
    {"Brooktree", "Conexant", "www.brooktree.com"},
    {"Atheros", "Atheros Communications", "www.atheros.com"},
    {"MATSHITA", "Panasonic", "www.panasonic.com"},
    {"Silicon Image", "Silicon Image", "www.siliconimage.com"},
    {"Silicon Integrated Image", "Silicon Image", "www.siliconimage.com"},
    {"KYE", "KYE Systems", "www.genius-kye.com"},
    {"Broadcom", "Broadcom", "www.broadcom.com"},
    {"Apple", "Apple", "www.apple.com"},
    {"IBM", "IBM", "www.ibm.com"},
    {"Dell", "Dell Computer", "www.dell.com"},
    {"Logitech", "Logitech International", "www.logitech.com"},
    {"FUJITSU", "Fujitsu", "www.fujitsu.com"},
    {"CDU", "Sony", "www.sony.com"},
    {"SanDisk", "SanDisk", "www.sandisk.com"},
    {"ExcelStor", "ExcelStor Technology", "www.excelstor.com"},
    {"D-Link", "D-Link", "www.dlink.com.tw"},
    {"Giga-byte", "Gigabyte Technology", "www.gigabyte.com.tw"},
    {"Gigabyte", "Gigabyte Technology", "www.gigabyte.com.tw"},
    {"C-Media", "C-Media Electronics", "www.cmedia.com.tw"},
    {"Avermedia", "AVerMedia Technologies", "www.aver.com"},
    {"Philips", "Philips", "www.philips.com"},
    {"RaLink", "Ralink Technology", "www.ralinktech.com"},
    {"Siemens", "Siemens AG", "www.siemens.com"},
    {"HP", "Hewlett-Packard", "www.hp.com"},
    {"Hewlett-Packard", "Hewlett-Packard", "www.hp.com"},
    {"TEAC", "TEAC America", "www.teac.com"},
    {"Microsoft", "Microsoft", "www.microsoft.com"},
    {"Memorex", "Memorex Products", "www.memorex.com"},
    {"eMPIA", "eMPIA Technology", "www.empiatech.com.tw"},
    {"Canon", "Canon", "www.canon.com"},
    {"A4Tech", "A4tech", "www.a4tech.com"},
    {"ALCOR", "Alcor", "www.alcor.org"},
    {"Vimicro", "Vimicro", "www.vimicro.com"},
    {"OTi", "Ours Technology", "www.oti.com.tw"},
    {"BENQ", "BenQ", "www.benq.com"},
    {"Acer", "Acer", "www.acer.com"},
    {"QUANTUM", "Quantum", "www.quantum.com"},
    {"Kingston", "Kingston", "www.kingston.com"},
    {"Chicony", "Chicony", "www.chicony.com.tw"},
    {"Genius", "Genius", "www.genius.ru"},
    /* BIOS manufacturers */
    {"American Megatrends", "American Megatrends", "www.ami.com"},
    {"Award", "Award Software International", "www.award-bios.com"},
    {"Phoenix", "Phoenix Technologies", "www.phoenix.com"},
    /* x86 vendor strings */
    { "AMDisbetter!", "Advanced Micro Devices", "www.amd.com" },
    { "AuthenticAMD", "Advanced Micro Devices", "www.amd.com" },
    { "CentaurHauls", "VIA (formerly Centaur Technology)", "www.via.tw" },
    { "CyrixInstead", "Cyrix", "" },
    { "GenuineIntel", "Intel", "www.intel.com" },
    { "TransmetaCPU", "Transmeta", "" },
    { "GenuineTMx86", "Transmeta", "" },
    { "Geode by NSC", "National Semiconductor", "" },
    { "NexGenDriven", "NexGen", "" },
    { "RiseRiseRise", "Rise Technology", "" },
    { "SiS SiS SiS", "Silicon Integrated Systems", "" },
    { "UMC UMC UMC", "United Microelectronics Corporation", "" },
    { "VIA VIA VIA", "VIA", "www.via.tw" },
    { "Vortex86 SoC", "DMP Electronics", "" },
    /* x86 VM vendor strings */
    { "KVMKVMKVM", "KVM", "" },
    { "Microsoft Hv", "Microsoft Hyper-V", "www.microsoft.com" },
    { "lrpepyh vr", "Parallels", "" },
    { "VMwareVMware", "VMware", "" },
    { "XenVMMXenVMM", "Xen HVM", "" },
};

}  // namespace

QString getVendorName(const QString& id) {
  for (const auto& vendor : kVendorList) {
    if (id.contains(vendor.id)) {
      return vendor.name;
    }
  }
  return {};
}

QString getVendorUrl(const QString& id) {
  for (const auto& vendor : kVendorList) {
    if (id.contains(vendor.id)) {
      return vendor.url;
    }
  }
  return {};
}

}  // namespace sysinfo