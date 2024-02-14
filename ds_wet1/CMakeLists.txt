cmake_minimum_required(VERSION 3.23.2)
project(wet1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        binary_tree.h
        Node.h
        nodetest.cpp
    )
