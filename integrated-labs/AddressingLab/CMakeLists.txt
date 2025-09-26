cmake_minimum_required(VERSION 3.10)

project(addressinglab C ASM)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)

### Executables

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(C_FILES src/addressinglab.c)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    if(UNIX)
        set(ASM_FILES src/caesarcipher.s)
    else()
        message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
    endif()
else()
    message(FATAL_ERROR "Unsupported processor architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

add_executable(addressinglab ${C_FILES} ${ASM_FILES})

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(addressinglab PRIVATE -w)
    else()
        target_compile_options(addressinglab PRIVATE
            -Wall
            -Wextra
        )
    endif()
    target_compile_options(addressinglab PRIVATE -Og)
endif()
