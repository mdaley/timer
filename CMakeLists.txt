cmake_minimum_required(VERSION 3.16)

if (NOT "${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/build")
    message(FATAL_ERROR "In-source builds are disabled.
    Please create a subfolder ./build and use `cmake ..` inside it.
    NOTE: cmake has created CMakeCache.txt and CMakeFiles/*.
          You must delete them, or cmake will refuse to work.")
endif()

project(timer)
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(Catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_TAG "v2.13.0")
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

FetchContent_Declare(plog
        GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
        GIT_TAG "1.1.5")
FetchContent_GetProperties(plog)
if(NOT plog_POPULATED)
    FetchContent_Populate(plog)
    add_subdirectory(${plog_SOURCE_DIR} ${plog_BINARY_DIR})
endif()

include(ExternalProject)
ExternalProject_Add(libconfig
        GIT_REPOSITORY https://github.com/hyperrealm/libconfig.git
        # Latest version doesn't work but master does, so use latest commit!
        GIT_TAG "f53e5de4528b47195f9a02c502e4f244070b0468"
        PREFIX "_deps/libconfig"
        SOURCE_DIR ${libconfig_SOURCE_DIR}
        BUILD_IN_SOURCE 1
        CMAKE_CACHE_ARGS
            -DBUILD_EXAMPLES:BOOL=OFF
            -DBUILD_TESTS:BOOL=OFF)

ExternalProject_Get_Property(libconfig SOURCE_DIR)
message("libconfig Source Dir = ${SOURCE_DIR}")
set(libconfig_SOURCE_DIR ${SOURCE_DIR})

add_library(timer src/RootTimer.cpp)
target_include_directories(timer PUBLIC src ${plog_SOURCE_DIR}/include)

add_executable(main src/main.cpp src/Config.cpp src/Config.h)
target_include_directories(main PRIVATE ${plog_SOURCE_DIR}/include ${libconfig_SOURCE_DIR}/lib)
target_link_libraries(main PRIVATE timer ${libconfig_SOURCE_DIR}/out/libconfig++.dylib)

add_executable(unit_tests test/RootTimerTests.cpp)
target_include_directories(unit_tests PRIVATE ${catch2_SOURCE_DIR}/single_include/catch2 )
target_link_libraries(unit_tests Catch2::Catch2 plog)

include(CTest)
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(unit_tests)
