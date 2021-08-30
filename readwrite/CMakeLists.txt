cmake_minimum_required(VERSION 3.19)
project(readwrite)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall
        -Wextra
)

add_executable(readwrite
        main.cpp
        )

target_link_libraries(readwrite pthread)