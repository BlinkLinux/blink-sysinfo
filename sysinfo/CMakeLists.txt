cmake_minimum_required(VERSION 3.10)
project(sysinfo
    VERSION 0.1.1
    LANGUAGES C CXX
    )

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Default build type: Release" FORCE)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json project file.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Enable unittests" OFF)

if (BUILD_TESTING)
  enable_testing()
endif ()

add_custom_target(generate-deps
    COMMAND mkdir -pv ${CMAKE_BINARY_DIR}/deps
    COMMAND cmake --graphviz=deps/deps.dot ..
    COMMAND dot -Tsvg -o deps/deps.svg deps/deps.dot
    COMMAND setsid xdg-open deps/deps.svg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_subdirectory(src)
