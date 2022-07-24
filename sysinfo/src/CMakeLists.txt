
add_subdirectory(third_party)

find_package(Qt5 5.12 COMPONENTS Core Network Gui REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set current directory as root of header files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(app)
add_subdirectory(base)
add_subdirectory(config)
add_subdirectory(controllers)
add_subdirectory(formats)
add_subdirectory(modules)
add_subdirectory(tests)
