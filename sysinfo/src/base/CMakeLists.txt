
set(SOURCE_FILES
    file.cpp
    file.h
    process.cpp
    process.h
    string.cpp
    string.h
    unit.cpp
    unit.h
    )
set(TEST_FILES
    string_test.cpp
    unit_test.cpp
    )

add_library(sysinfo-base STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(sysinfo-base
    Qt5::Core
    )

if (BUILD_TESTING)
  add_executable(sysinfo-base-tests
      ${TEST_FILES}
      )
  target_link_libraries(sysinfo-base-tests
      Qt5::Core

      sysinfo-base
      sysinfo-tests
      )
  add_test(sysinfo-base-tests sysinfo-base-tests)
endif()
