
set(SOURCE_FILES
    computer/uptime_info.cpp
    computer/uptime_info.h
    )

add_library(sysinfo-formats STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-formats
    Qt5::Core
    )