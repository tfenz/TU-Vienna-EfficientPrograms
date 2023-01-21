cmake_minimum_required(VERSION 3.20)
project(ramanujan_numbers)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-Wall -g")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -O3")
endif ()

include_directories(./include)

add_executable(naive_hashset src/naive_hashset.cpp)
add_executable(naive_hashset_unordered src/naive_hashset_unordered.cpp)
add_executable(bucket_hashing src/bucket_hashing.cpp)
add_executable(optimized_ramanujan_no_struct stuff/optimized_ramanujan_no_struct.cpp)
add_executable(ramanujan_rehashing src/ramanujan_rehashing.cpp)
add_executable(ramanujan_2hashsets_unordered src/ramanujan_2hashsets_unordered.cpp )
add_executable(3loops src/3loops.cpp)
add_executable(collision_evaluation src/collision_evaluation.cpp)
add_executable(collision_evaluation_rehashing src/collision_evaluation_rehashing.cpp)

