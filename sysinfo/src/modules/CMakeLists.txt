
set(SOURCE_FILES
    computer/bootup.cpp
    computer/bootup.h
    computer/environment.cpp
    computer/environment.h
    computer/group.cpp
    computer/group.h
    computer/operation_system.cpp
    computer/operation_system.h
    computer/uptime.cpp
    computer/uptime.h
    computer/user.cpp
    computer/user.h
    )

set(TEST_FILES
    computer/bootup_test.cpp
    computer/group_test.cpp
    computer/operation_system_test.cpp
    computer/uptime_test.cpp
    computer/user_test.cpp
    )

add_library(sysinfo-modules STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-modules
    Qt5::Core

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
