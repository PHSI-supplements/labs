cmake_minimum_required(VERSION 3.10)

project(floatlab C)

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
        src/bits-to-string.h    src/bits-to-string.c
        src/fpu.h               src/fpu.c
        src/unnormal.h          src/unnormal.c
)

### Executables

add_executable(floatlab src/floatlab.c)

target_link_libraries(floatlab PRIVATE student_code)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(floatlab PRIVATE -w)
    else()
        target_compile_options(floatlab PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
        )
    endif()
    target_compile_options(floatlab PRIVATE -Og)
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
        ${CMAKE_SOURCE_DIR}/test/floatlab.json
)

add_test(
        NAME no_float_literals
        COMMAND sh -c
        "if grep -E '([0-9]\\.|\\.[0-9])' ${CMAKE_SOURCE_DIR}/src/fpu.c \
        | grep -v -E '\"[^\"]*\"' \
        | grep -v -E '//' \
        | grep -v 'Reports whether a number is'; then
         echo 'ERROR: floating-point literal(s) detected in fpu.c' >&2
         exit 1
     else
         exit 0
     fi"
)

