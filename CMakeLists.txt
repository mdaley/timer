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

FetchContent_Declare(Catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_TAG "v2.13.0")
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

add_library(timer src/RootTimer.cpp)
target_include_directories(timer PUBLIC src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE timer)
add_executable(unit_tests test/RootTimerTests.cpp)
target_include_directories(unit_tests PRIVATE ${catch2_SOURCE_DIR}/single_include/catch2)
target_link_libraries(unit_tests Catch2)
