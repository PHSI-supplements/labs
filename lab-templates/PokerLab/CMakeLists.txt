cmake_minimum_required(VERSION 3.10)

project(pokerlab C)

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
        src/card.h              src/card.c
        src/poker.h             src/poker.c
)

### Executables

add_executable(pokerlab src/pokerlab.c)

target_link_libraries(pokerlab PRIVATE student_code)

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

### Unit Tests

file (GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)

foreach (test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} test/unit-tests.h)
    target_link_libraries(${test_name} PRIVATE student_code)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()

### Constraint Check

find_package(Python3 REQUIRED)

add_test(
        NAME ConstraintCheck
        COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/constraint-check.py
        ${CMAKE_SOURCE_DIR}/test/pokerlab.json
)


