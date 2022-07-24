
set(SOURCE_FILES
    computer/boots.cpp
    computer/boots.h
    computer/environment.h
    computer/groups.cpp
    computer/groups.h
    computer/languages.cpp
    computer/languages.h
    computer/operation_system.cpp
    computer/operation_system.h
    computer/uptime.cpp
    computer/uptime.h
    computer/users.cpp
    computer/users.h
    )

add_library(sysinfo-formats STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-formats
    Qt5::Core
    )