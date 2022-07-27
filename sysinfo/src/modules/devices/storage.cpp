// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/storage.h"

#include <QDebug>
#include <QScopedPointer>

#include <udisks2-qt5/dblockdevice.h>
#include <udisks2-qt5/dblockpartition.h>
#include <udisks2-qt5/ddiskdevice.h>
#include <udisks2-qt5/ddiskmanager.h>

namespace sysinfo {
namespace devices {
namespace {

bool getDiskDeviceInfo(const QString& device_path, StorageDisk& disk) {
  QScopedPointer<DDiskDevice> disk_device(DDiskManager::createDiskDevice(device_path));
  disk.path = disk_device->path();
  disk.configuration = disk_device->configuration();
  disk.connection_bus = disk_device->connectionBus();
  disk.id = disk_device->id();
  disk.media = disk_device->media();
  disk.media_compatibility = disk_device->mediaCompatibility();
  disk.model = disk_device->model();
  disk.revision = disk_device->model();
  disk.seat = disk_device->seat();
  disk.seat = disk_device->serial();
  disk.sibling_id = disk_device->siblingId();
  disk.sort_key = disk_device->sortKey();
  disk.vendor = disk_device->vendor();
  disk.wwn = disk_device->WWN();

  disk.size = disk_device->size();
  disk.time_detected = disk_device->timeDetected();
  disk.time_media_detected = disk_device->timeMediaDetected();
  disk.rotation_rate = disk_device->rotationRate();
  disk.can_power_off = disk_device->canPowerOff();
  disk.can_eject = disk_device->ejectable();
  disk.is_removable = disk_device->removable();
  disk.media_available = disk_device->mediaAvailable();
  disk.is_optical = disk_device->optical();
  disk.optical_is_blank = disk_device->opticalBlank();

  return true;
}

}  // namespace

bool getStorageList(StorageList& list) {
  QScopedPointer<DDiskManager> manager(new DDiskManager);
  const auto devices = manager->diskDevices();
  bool ok = true;

  for (const auto& path : devices) {
    qDebug() << "device:" << path;
    StorageDisk disk;
    if (getDiskDeviceInfo(path, disk)) {
      list.append(disk);
    } else {
      ok = false;
    }
  }

  return ok;
}

}  // namespace devices
}  // namespace sysinfo