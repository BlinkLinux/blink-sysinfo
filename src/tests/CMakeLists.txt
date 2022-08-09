
set(SOURCES
    qt_test_main.cpp
    )

if (BUILD_TESTING)
  find_package(GTest REQUIRED)
  add_library(sysinfo-tests STATIC
      ${SOURCES}
      )
  target_link_libraries(sysinfo-tests
      Qt5::Core
      GTest::GTest
      )
endif()
