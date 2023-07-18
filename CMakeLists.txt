cmake_minimum_required(VERSION 3.20)
project(findNumber)

set(CMAKE_CXX_STANDARD 20)

add_executable(findNumber
        main.cpp
        game.cpp game.h
        getRandomNumber.cpp getRandomNumber.h inputFiler.cpp inputFiler.h fileTable.cpp fileTable.h)

target_compile_options(findNumber PUBLIC
        -Wall
        )
