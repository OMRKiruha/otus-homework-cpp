cmake_minimum_required(VERSION 3.20)
project(conteiners)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
endif()

#message("This is normal")
#message("${Red}This is Red${ColourReset}")
#message("${Green}This is Green${ColourReset}")
#message("${Yellow}This is Yellow${ColourReset}")
#message("${Blue}This is Blue${ColourReset}")


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-liblsan -static-libasan -static-libubsan -static-libgcc") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-liblsan -static-libasan -static-libubsan -static-libgcc") # для того чтобы можно было запускать приложение в Windows двойным
    #кликом и из командной строки без прописывания в PATH путей к бинарникам libstdc++
elseif(...)

endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(conteiners
        main.cpp
        MyVector.h
        MyList.h
        MyForwardList.h)

target_compile_options(conteiners PUBLIC
        -g
        -Wall
        -Wextra
        -pedantic
        #-fsanitize=leak
        #-fsanitize=address
        #-fsanitize=undefined
        )

#set(COMM_SANITIZER "-fsanitize=address -fsanitize=undefined -fsanitize-recover=all")
#set(CMAKE_CXX_FLAGS ${COMM_SANITIZER})
#set(DCMAKE_C_FLAGS ${COMM_SANITIZER})
#set(CMAKE_EXE_LINKER_FLAGS ${COMM_SANITIZER})

set(WITH_TESTS ON CACHE BOOL "" FORCE)
if (WITH_TESTS)
    find_package(googletest)
    if(NOT googletest_FOUND)
        message("${Yellow}==> !!! GoogleTest not found${ColourReset}")
        include(FetchContent)
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG        v1.14.0
        )
        FetchContent_MakeAvailable(googletest)
        message("${Green}==> !!! FetchContent GoogleTest from GIT${ColourReset}")
    endif()

    # Test target
    add_executable(containers_tests
            ${CMAKE_CURRENT_LIST_DIR}/tests/MyVector_tests.cpp
    )

    # Link test target against gtest libraries
    target_link_libraries(containers_tests PRIVATE
            gtest
            gmock
            gtest_main
    )
    set_target_properties(containers_tests PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            GTEST_COLOR ON
            )
    target_compile_options(containers_tests PUBLIC
            -g
            -Wall
            -Wextra
            -pedantic
            #-fsanitize=leak
            #-fsanitize=address
            #-fsanitize=undefined
            )

    #set(COMM_SANITIZER "-fsanitize=address -fsanitize=undefined -fsanitize-recover=all")
    #set(CMAKE_CXX_FLAGS ${COMM_SANITIZER})
    #set(DCMAKE_C_FLAGS ${COMM_SANITIZER})
    #set(CMAKE_EXE_LINKER_FLAGS ${COMM_SANITIZER})
endif ()