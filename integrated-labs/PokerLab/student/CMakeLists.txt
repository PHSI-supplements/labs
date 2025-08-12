cmake_minimum_required(VERSION 3.10)

project(pokerlab C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.c)
file(GLOB HDR_FILES CONFIGURE_DEPENDS src/*.h)      # some IDEs need this

add_executable(pokerlab ${SRC_FILES} ${HDR_FILES})

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(pokerlab PRIVATE -w)
    else()
        target_compile_options(pokerlab PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
        )
    endif()
    target_compile_options(pokerlab PRIVATE -O0)    # for debugger demonstration
endif()
