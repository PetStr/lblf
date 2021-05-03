cmake_minimum_required(VERSION 3.17)

project("lblf")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(ZLIB)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-switch")

add_executable(read read.cc print.cc)
target_link_libraries(read -lz )

add_executable(read_base read_base.cc print.cc)
target_link_libraries(read_base -lz )

add_executable(count_id count_id.cc print.cc)

add_executable(tell_gear tell_gear.cc print.cc)

