cmake_minimum_required(VERSION 3.10)

project(integerlab C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_library(student_code STATIC
        src/alu.h                       src/alu.c
                                        src/basetwo.c
        src/authoritative_results.h     src/authoritative_results.c
        src/profiler.h                  src/profiler.c
)

set(STD_LIB  m)

### Executables

add_executable(integerlab src/integerlab.c)

target_link_libraries(integerlab PRIVATE student_code ${STD_LIB})

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(integerlab PRIVATE -w)
    else()
        target_compile_options(integerlab PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -finstrument-functions
        )
    endif()
    target_compile_options(integerlab PRIVATE -Og)
endif()

### Unit Tests

file (GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)

foreach (test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} test/unit-tests.h)
    target_link_libraries(${test_name} PRIVATE student_code ${STD_LIB})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()

### Constraint Check

find_package(Python3 REQUIRED)

add_test(
        NAME ConstraintCheck
        COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/constraint-check.py
        ${CMAKE_SOURCE_DIR}/test/integerlab.json
)


