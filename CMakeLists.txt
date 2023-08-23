cmake_minimum_required(VERSION 3.5)

project("P2P_Navy" LANGUAGES CXX)

add_definitions(
    "-fPIC"
    "-g"
    "-g3"
    "-Wall"
    "-Wextra"
    "-lboost_date_time"
    "-lboost_serialization"
    "-lboost_system"
    "-lboost_thread"
    "-lpthread"
)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

SET(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -pthread -fPIC -g -g3 -Wall -Wextra -lboost_date_time -lboost_serialization -lboost_system -lboost_thread -lpthread"
)

SET(
    includes
    "${PROJECT_SOURCE_DIR}/include"
)

include_directories(${CMAKE_INCLUDE_PATH})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB P2P_Navy_SourceFiles src/*.cpp)
# file(GLOB ClientSourceFiles src/client/src/*.cpp)
# file(GLOB GameEnigneSourceFiles src/gameEngine/*/src/*.cpp)
# file(GLOB UtilsSourceFiles src/utils/*/src/*.cpp)
# file(GLOB FactoryrSourceFiles src/factory/src/*.cpp)
# file(GLOB gameObjectsSourceFiles src/gameObjects/src/*.cpp)

add_executable("P2P_Navy" ${P2P_Navy_SourceFiles})

find_package(Boost 1.83.0 COMPONENTS system serialization thread REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries("P2P_Navy" ${Boost_LIBRARIES})
endif()

install(TARGETS "P2P_Navy" DESTINATION bin)

target_include_directories("P2P_Navy" PUBLIC ${includes})