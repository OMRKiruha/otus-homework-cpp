cmake_minimum_required(VERSION 3.20)
project(multithread)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-liblsan -static-libasan -static-libubsan -static-libgcc") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-liblsan -static-libasan -static-libubsan -static-libgcc") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(...)

endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(singlethread
        topk_words.cpp
        common_func.cpp)

add_executable(multithread_async
        topk_words_mt_async.cpp
        common_func.cpp)

target_compile_options(singlethread PUBLIC
        -g
        -Wall
        -Wextra
        -pedantic
        #-O2
        #-fsanitize=leak
        #-fsanitize=address
        #-fsanitize=undefined
        )

target_compile_options(multithread_async PUBLIC
        -g
        -Wall
        -Wextra
        -pedantic
        #-O2
        #-fsanitize=leak
        #-fsanitize=address
        #-fsanitize=undefined
)

#set(COMM_SANITIZER "-fsanitize=address -fsanitize=undefined -fsanitize-recover=all")
#set(CMAKE_CXX_FLAGS ${COMM_SANITIZER})
#set(DCMAKE_C_FLAGS ${COMM_SANITIZER})
#set(CMAKE_EXE_LINKER_FLAGS ${COMM_SANITIZER})