// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/storage.h"

#include <QDebug>
#include <QScopedPointer>
#include <QDBusArgument>
#include <QDBusMetaType>

#include <udisks2-qt5/dblockdevice.h>
#include <udisks2-qt5/dblockpartition.h>
#include <udisks2-qt5/ddiskdevice.h>
#include <udisks2-qt5/ddiskmanager.h>

namespace sysinfo {
namespace devices {
namespace {

void registerDBusObjects() {
  qDBusRegisterMetaType<QMap<QString, QVariantMap>>();
  qDBusRegisterMetaType<QList<QPair<QString, QVariantMap>>>();
  qDBusRegisterMetaType<QByteArrayList>();
  qDBusRegisterMetaType<QPair<QString, QVariantMap>>();
  qDBusRegisterMetaType<QMap<QDBusObjectPath, QMap<QString, QVariantMap>>>();

  QMetaType::registerDebugStreamOperator<QList<QPair<QString, QVariantMap>>>();
}

QStringList toStringList(const QByteArrayList& list) {
  QStringList result;
  for (const auto& item: list) {
    result.append(item.trimmed());
  }
  return result;
}

bool getBlockPartitionInfo(const QString& path, BlockPartition& partition) {
  QScopedPointer<DBlockPartition> block_partition(DDiskManager::createBlockPartition(path));
  partition.flags = block_partition->flags();
  partition.is_contained = block_partition->isContained();
  partition.is_container = block_partition->isContainer();
  partition.name = block_partition->name();
  partition.number = block_partition->number();
  partition.offset = block_partition->offset();
  partition.size = block_partition->size();
  partition.table = block_partition->table();
  partition.type = block_partition->type();
  partition.mbr_type = static_cast<MBRType>(block_partition->eType());
  partition.gpt_type = static_cast<GPTType>(block_partition->guidType());
  partition.uuid = block_partition->UUID();

  return true;
}

bool getBlockDeviceInfo(const QString& path, BlockDevice& device) {
  QScopedPointer<DBlockDevice> block_device(DDiskManager::createBlockDevice(path));
  device.path = block_device->path();
  device.crypto_backing_device = block_device->cryptoBackingDevice();
  device.device = block_device->device().trimmed();
  device.drive = block_device->drive();
  device.hint_name = block_device->hintName();
  device.id = block_device->id();
  device.id_label = block_device->idLabel();
  device.id_type = block_device->idType();
  device.id_uuid = block_device->idUUID();
  device.id_usage = block_device->idUsage();
  device.id_version = block_device->idVersion();
  device.md_raid = block_device->mDRaid();
  device.md_raid_member = block_device->mDRaidMember();
  device.preferred_device = block_device->preferredDevice();
  device.symbolic_links = toStringList(block_device->symlinks());
  device.user_space_mount_options = block_device->userspaceMountOptions();

  device.mount_points = toStringList(block_device->mountPoints());

  device.device_number = block_device->deviceNumber();
  device.size = block_device->size();

  device.fs_type = static_cast<FSType>(block_device->fsType());

  device.pt_type = static_cast<PTType>(block_device->ptType());

  device.has_filesystem = block_device->hasFileSystem();
  device.has_partition = block_device->hasPartition();
  device.is_encrypted = block_device->isEncrypted();
  device.is_loop_device = block_device->isLoopDevice();
  device.hint_auto = block_device->hintAuto();
  device.hint_ignore = block_device->hintIgnore();
  device.hint_can_make_partition = block_device->hintPartitionable();
  device.hint_system = block_device->hintSystem();
  device.read_only = block_device->readOnly();

  if (device.has_partition) {
    getBlockPartitionInfo(path, device.partition);
  }

  return true;
}

bool getDiskDeviceInfo(const QString& device_path, StorageDisk& disk) {
  QScopedPointer<DDiskDevice> disk_device(DDiskManager::createDiskDevice(device_path));
  disk.path = disk_device->path();
  disk.connection_bus = disk_device->connectionBus();
  disk.id = disk_device->id();
  disk.media = disk_device->media();
  disk.media_compatibility = disk_device->mediaCompatibility();
  disk.model = disk_device->model();
  disk.revision = disk_device->model();
  disk.seat = disk_device->seat();
  disk.serial = disk_device->serial();
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
  registerDBusObjects();

  QScopedPointer<DDiskManager> manager(new DDiskManager);

  for (const auto& path: manager->diskDevices()) {
    StorageDisk disk;
    getDiskDeviceInfo(path, disk);
    list.append(disk);
  }

  QVector<BlockDevice> block_devices;
  for (const auto& path: DDiskManager::blockDevices({})) {
    BlockDevice device;
    getBlockDeviceInfo(path, device);
    block_devices.append(device);
  }

  for (auto& block_device: block_devices) {
    for (auto& disk: list) {
      if (block_device.drive == disk.path) {
        disk.block_devices.append(block_device);
        break;
      }
    }
  }

  return true;
}

}  // namespace devices
}  // namespace sysinfo