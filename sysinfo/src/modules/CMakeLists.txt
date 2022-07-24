
set(SOURCE_FILES
    computer/boots.cpp
    computer/boots.h
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
    computer/modules.cpp
    computer/modules.h
    computer/operation_system.cpp
    computer/operation_system.h
    computer/uptime.cpp
    computer/uptime.h
    computer/users.cpp
    computer/users.h
    )

set(TEST_FILES
    computer/boots_test.cpp
    computer/development_test.cpp
    computer/display_test.cpp
    computer/filesystem_test.cpp
    computer/groups_test.cpp
    computer/languages_test.cpp
    computer/modules_test.cpp
    computer/operation_system_test.cpp
    computer/uptime_test.cpp
    computer/users_test.cpp
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
