cmake_minimum_required(VERSION 3.20)
project(conteiners)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_EXE_LINKER_FLAGS "-static") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
    set(CMAKE_EXE_LINKER_FLAGS "-static") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(...)

endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(conteiners
        main.cpp
        MyVector.h
        MyList.h)

target_compile_options(conteiners PUBLIC
        -Wall

        )
