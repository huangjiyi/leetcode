cmake_minimum_required(VERSION 3.22)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(linklist)
include_directories(stackNqueue)

add_executable(algorithm
        string/main.cpp)
