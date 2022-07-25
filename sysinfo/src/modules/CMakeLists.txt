
set(SOURCE_FILES
    computer/boots.cpp
    computer/boots.h
    computer/computer.cpp
    computer/computer.h
    computer/development.cpp
    computer/development.h
    computer/display.cpp
    computer/display.h
    computer/environment.cpp
    computer/environment.h
    computer/filesystem.cpp
    computer/filesystem.h
    computer/groups.cpp
    computer/groups.h
    computer/languages.cpp
    computer/languages.h
    computer/memory.cpp
    computer/memory.h
    computer/modules.cpp
    computer/modules.h
    computer/operation_system.cpp
    computer/operation_system.h
    computer/uptime.cpp
    computer/uptime.h
    computer/users.cpp
    computer/users.h

    devices/battery.cpp
    devices/battery.h
    devices/dmi.cpp
    devices/dmi.h
    devices/input_devices.cpp
    devices/input_devices.h
    devices/memory.cpp
    devices/memory.h
    devices/pci.cpp
    devices/pci.h
    devices/usb.cpp
    devices/usb.h

    network/arp_table.cpp
    network/arp_table.h
    network/dns_servers.cpp
    network/dns_servers.h
    network/interfaces.cpp
    network/interfaces.h
    network/ip_connections.cpp
    network/ip_connections.h
    network/routing_table.cpp
    network/routing_table.h

    shared/vendor.cpp
    shared/vendor.h
    )

set(TEST_FILES
    computer/boots_test.cpp
    computer/computer_test.cpp
    computer/development_test.cpp
    computer/display_test.cpp
    computer/filesystem_test.cpp
    computer/groups_test.cpp
    computer/languages_test.cpp
    computer/memory_test.cpp
    computer/modules_test.cpp
    computer/operation_system_test.cpp
    computer/uptime_test.cpp
    computer/users_test.cpp

    devices/battery_test.cpp
    devices/dmi_test.cpp
    devices/input_devices_test.cpp
    devices/memory_test.cpp
    devices/pci_test.cpp
    devices/usb_test.cpp

    network/arp_table_test.cpp
    network/dns_servers_test.cpp
    network/interfaces_test.cpp
    network/ip_connections_test.cpp
    network/routing_table_test.cpp

    shared/vendor_test.cpp
    )

add_library(sysinfo-modules STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-modules
    Qt5::Core
    Qt5::Gui

    sysinfo-base
    sysinfo-formats
    )

if (BUILD_TESTING)
  add_executable(sysinfo-modules-tests
      ${TEST_FILES}
      )
  target_link_libraries(sysinfo-modules-tests
      Qt5::Core

      sysinfo-modules
      sysinfo-tests
      )
  add_test(sysinfo-modules-tests sysinfo-modules-tests)
endif()
