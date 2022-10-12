cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(linklist)
include_directories(stackNqueue)

add_executable(test
        test.cpp)

add_executable(hash
        hash/main.cpp
        utils.h)

add_executable(double_pointer
        double_pointer/main.cpp
        utils.h)

add_executable(tree
        tree/main.cpp
        utils.h)