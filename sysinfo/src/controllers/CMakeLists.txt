
set(SOURCE_FILES
    shell.cpp
    shell.h
    )

add_library(sysinfo-controllers STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-controllers
    Qt5::Core

    CuteLogger

    sysinfo-base
    sysinfo-config
    sysinfo-modules
    )