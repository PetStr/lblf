cmake_minimum_required(VERSION 3.31)

project("lblf")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CXX_STANDARD 20)

find_package(ZLIB)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-switch -std=c++20")

add_executable(read read.cc print.cc blf_reader.cc)
target_link_libraries(read -lz )

#add_executable(read_base read_base.cc print.cc)
#target_link_libraries(read_base -lz )

#add_executable(sand sand.cc print.cc)
#target_link_libraries(sand -lz )

add_executable(count_id count_id.cc print.cc)

add_executable(print_structs print_structs.cc)

#add_executable(deque_replenish deque_replenish.cc)

#add_executable(deque_example deque_example.cc)

#add_executable(variant variant.cc)
#add_executable(tell_gear tell_gear.cc print.cc)

