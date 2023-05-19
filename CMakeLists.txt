cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(linklist)
include_directories(stackNqueue)

add_executable(test test.cpp utils.h)

add_executable(hash hash/main.cpp)

add_executable(double_pointer
        double_pointer/main.cpp)

add_executable(tree
        tree/main.cpp)

add_executable(back_tracking
        back_tracking/main.cpp
        greedy/main.cpp)

add_executable(greedy greedy/main.cpp)

add_executable(dp dynamic_programming/main.cpp)