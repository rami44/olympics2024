cmake_minimum_required(VERSION 3.24)
project(wet1)

set(CMAKE_CXX_STANDARD 14)

include_directories(ds_wet1)

add_executable(wet1
        ds_wet1/binary_tree.h
        ds_wet1/Node.h
        ds_wet1/nodetest.cpp

        ds_wet1/binary_tree.h)
