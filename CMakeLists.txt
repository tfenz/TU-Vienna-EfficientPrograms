cmake_minimum_required(VERSION 3.20)
project(ramanujan_numbers)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-Wall -O0 -g")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -O3")
endif ()

include_directories(./include)

add_executable(ramanujan_numbers src/naive_ramanujan.cpp)
add_executable(ramanujan_numbers_optimized src/optimized_ramanujan.cpp)
