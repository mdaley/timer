cmake_minimum_required(VERSION 3.16)

if (NOT "${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/build")
    message(FATAL_ERROR "In-source builds are disabled.
    Please create a subfolder ./build and use `cmake ..` inside it.
    NOTE: cmake has created CMakeCache.txt and CMakeFiles/*.
          You must delete them, or cmake will refuse to work.")
endif()

project(timer)

set(CMAKE_CXX_STANDARD 11)
add_executable(timer main.cpp)
