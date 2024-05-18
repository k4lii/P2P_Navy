cmake_minimum_required(VERSION 3.5)
project(P2P_Navy LANGUAGES CXX)

# Include Conan toolchain for setup
include(${CMAKE_SOURCE_DIR}/conan_toolchain.cmake)

# Add the directory where the header files are located
include_directories("${PROJECT_SOURCE_DIR}/include")

# Locate necessary packages


# target_link_libraries(P2P_Navy ${CURSES_LIBRARIES})
find_package(Boost REQUIRED)
find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(libbacktrace REQUIRED)  # Confirm the package name
find_package(Curses REQUIRED)        # Add this line to find ncurses

# Include Boost and Curses directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURSES_INCLUDE_DIRS})

# Add your executable
add_executable(P2P_Navy src/main.cpp src/HandleTurns.cpp src/InitMaps.cpp src/Network.cpp src/VerifyBoatsFile.cpp src/menu.cpp)

# Link libraries
target_link_libraries(P2P_Navy PRIVATE Boost::boost ZLIB::ZLIB BZip2::BZip2 libbacktrace::libbacktrace ${CURSES_LIBRARIES})

# Set the build type to Debug to include debug symbols
set(CMAKE_BUILD_TYPE Debug)
