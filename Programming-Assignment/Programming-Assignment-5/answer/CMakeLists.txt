cmake_minimum_required(VERSION 3.12)
project(answer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(answer
        graph_test.cpp
        graph_test.h
        main.cpp)
