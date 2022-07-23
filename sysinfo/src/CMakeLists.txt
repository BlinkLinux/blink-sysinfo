
find_package(Qt5 5.12 COMPONENTS Network Svg Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(LINK_LIBS
    Qt5::Network
    Qt5::Svg
    Qt5::Widgets
    )

set(SOURCE_FILES

    )

## Targets
add_executable(sysinfo
    app/main.cpp
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo
    ${LINK_LIBS}
    )
target_include_directories(sysinfo
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )