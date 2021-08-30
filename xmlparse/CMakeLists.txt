cmake_minimum_required(VERSION 3.16)
project(xmlparse)

set(CMAKE_CXX_STANDARD 17)

add_executable(xmlparse
        main.cpp
        parser.cpp
        worker.cpp
        command.cpp)