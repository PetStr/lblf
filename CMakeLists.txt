cmake_minimum_required(VERSION 3.17)

project("lblf")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(ZLIB)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-switch")

add_executable(read read.cc print.cc)

target_link_libraries(read ZLIB::ZLIB)

add_executable(count_id count_id.cc)

