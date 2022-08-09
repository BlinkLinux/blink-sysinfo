
set(LINK_LIBS
    Qt5::Core

    sysinfo-controllers
    )

add_executable(sysinfo
    main.cpp
    )
target_link_libraries(sysinfo
    ${LINK_LIBS}
    )

## Installation
install(TARGETS sysinfo
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    )