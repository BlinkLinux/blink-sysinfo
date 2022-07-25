
set(SOURCE_FILES
    computer/boots.cpp
    computer/boots.h
    computer/development.cpp
    computer/development.h
    computer/environment.h
    computer/display.cpp
    computer/display.h
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

    devices/dmi.cpp
    devices/dmi.h
    devices/input_devices.cpp
    devices/input_devices.h
    devices/memory.h
    devices/pci.cpp
    devices/pci.h
    devices/usb.cpp
    devices/usb.h

    network/dns_servers.cpp
    network/dns_servers.h
    )

add_library(sysinfo-formats STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-formats
    Qt5::Core
    )