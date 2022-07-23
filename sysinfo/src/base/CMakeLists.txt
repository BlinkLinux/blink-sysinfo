
set(SOURCE_FILES
    file.cpp
    file.h
    )

add_library(sysinfo-base STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-base
    Qt5::Core
    )
