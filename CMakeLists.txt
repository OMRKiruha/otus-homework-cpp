cmake_minimum_required(VERSION 3.26)
project(findNumber)

set(CMAKE_CXX_STANDARD 20)

add_executable(findNumber main.cpp game.cpp game.h)

target_compile_options(findNumber PUBLIC
        -Wall
        )
