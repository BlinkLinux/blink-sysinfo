// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "formats/devices/storage.h"

namespace sysinfo {
namespace devices {

qint32 dump(MBRType type) {
  return static_cast<qint32>(type);
}

qint32 dump(GPTType type) {
  return static_cast<qint32>(type);
}

QJsonObject dump(const BlockPartition& partition) {
  QJsonObject obj;
  obj.insert("name", partition.name);
  obj.insert("table", partition.table);
  obj.insert("uuid", partition.uuid);
  obj.insert("type", partition.type);

  obj.insert("flags", static_cast<qint64>(partition.flags));
  obj.insert("offset", static_cast<qint64>(partition.offset));
  obj.insert("size", static_cast<qint64>(partition.size));
  obj.insert("number", static_cast<qint32>(partition.number));

  obj.insert("mbrType", dump(partition.mbr_type));
  obj.insert("gptType", dump(partition.gpt_type));

  obj.insert("isContained", partition.is_contained);
  obj.insert("isContainer", partition.is_container);
  return obj;
}

qint32 dump(FSType type) {
  return static_cast<qint32>(type);
}

qint32 dump(PTType type) {
  return static_cast<qint32>(type);
}

QJsonObject dump(const BlockDevice& device) {
  QJsonObject obj;
  obj.insert("path", device.path);
  obj.insert("cryptoBackingDevice", device.crypto_backing_device);
  obj.insert("device", device.device);
  obj.insert("drive", device.drive);
  obj.insert("hintName", device.hint_name);
  obj.insert("id", device.id);
  obj.insert("label", device.id_label);
  obj.insert("type", device.id_type);
  obj.insert("uuid", device.id_uuid);
  obj.insert("idUsage", device.id_usage);
  obj.insert("idVersion", device.id_version);
  obj.insert("mdRaid", device.md_raid);
  obj.insert("mdRaidMember", device.md_raid_member);
  obj.insert("preferredDevice", QString(device.preferred_device));
  obj.insert("symbolicLinks", QJsonArray::fromStringList(device.symbolic_links));
  obj.insert("userSpaceMountOptions", QJsonArray::fromStringList(device.user_space_mount_options));

  obj.insert("mountPoints", QJsonArray::fromStringList(device.mount_points));

  obj.insert("deviceNumber", static_cast<qint64>(device.device_number));
  obj.insert("size", static_cast<qint64>(device.size));

  obj.insert("fsType", dump(device.fs_type));

  obj.insert("ptType", dump(device.pt_type));

  obj.insert("hasFilesystem", device.has_filesystem);
  obj.insert("hasPartition", device.has_partition);
  obj.insert("isEncrypted", device.is_encrypted);
  obj.insert("isLoopDevice", device.is_loop_device);
  obj.insert("hintAuto", device.hint_auto);
  obj.insert("hintIgnore", device.hint_ignore);
  obj.insert("hintPartitionable", device.hint_can_make_partition);
  obj.insert("hintSystem", device.hint_system);
  obj.insert("readOnly", device.read_only);

  if (device.has_partition) {
    obj.insert("partition", dump(device.partition));
  }

  return obj;
}

QJsonObject dump(const StorageDisk& disk) {
  QJsonObject obj;
  obj.insert("path", disk.path);
  obj.insert("connectionBus", disk.connection_bus);
  obj.insert("id", disk.id);
  obj.insert("media", disk.media);
  obj.insert("mediaCompatibility", QJsonArray::fromStringList(disk.media_compatibility));
  obj.insert("model", disk.model);
  obj.insert("revision", disk.revision);
  obj.insert("seat", disk.seat);
  obj.insert("serial", disk.serial);
  obj.insert("siblingId", disk.sibling_id);
  obj.insert("sortKey", disk.sort_key);
  obj.insert("vendor", disk.vendor);
  obj.insert("wwn", disk.wwn);

  obj.insert("size", static_cast<qint64>(disk.size));
  obj.insert("timeDetected", static_cast<qint64>(disk.time_detected));
  obj.insert("timeMediaDetected", static_cast<qint64>(disk.time_media_detected));
  obj.insert("rotationRate", disk.rotation_rate);
  obj.insert("canPowerOff", disk.can_power_off);
  obj.insert("canEject", disk.can_eject);
  obj.insert("isRemovable", disk.is_removable);
  obj.insert("mediaAvailable", disk.media_available);
  obj.insert("isOptical", disk.is_optical);
  obj.insert("opticalIsBlank", disk.optical_is_blank);

  QJsonArray block_devices;
  for (const auto& device : disk.block_devices) {
    block_devices.append(dump(device));
  }
  obj.insert("blockDevices", block_devices);

  return obj;
}

QJsonArray dump(const StorageList& list) {
  QJsonArray array;
  for (const auto& item : list) {
    array.append(dump(item));
  }
  return array;
}

}  // namespace devices
}  // namespace sysinfo