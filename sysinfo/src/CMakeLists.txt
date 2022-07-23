
find_package(Qt5 5.12 COMPONENTS Core Network REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(LINK_LIBS
    Qt5::Core
    Qt5::Network
    )

set(SOURCE_FILES
    controllers/main_controller.cpp
    controllers/main_controller.h
    controllers/shell.cpp
    controllers/shell.h
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