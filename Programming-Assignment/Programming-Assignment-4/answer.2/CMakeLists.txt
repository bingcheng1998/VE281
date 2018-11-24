cmake_minimum_required(VERSION 3.12)
project(answer_old)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(answer_old
        equity_transfer.cpp
        equity_transfer.h
        main.cpp)
