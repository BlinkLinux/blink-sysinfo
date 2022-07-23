
set(SOURCE_FILES
    computer/uptime.cpp
    computer/uptime.h
    )

set(TEST_FILES
    computer/uptime_test.cpp
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
