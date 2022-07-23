
set(SOURCE_FILES
    computer/uptime.cpp
    computer/uptime.h
    )

add_library(sysinfo-modules STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-modules
    Qt5::Core

    sysinfo-formats
    )
