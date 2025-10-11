cmake_minimum_required(VERSION 3.10)

project(duplicatorlab C)

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

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.c)
file(GLOB HDR_FILES CONFIGURE_DEPENDS src/*.h)      # some IDEs need this

add_executable(duplicator ${SRC_FILES} ${HDR_FILES})

find_package(Threads REQUIRED)
target_link_libraries(duplicator PRIVATE Threads::Threads)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(duplicator PRIVATE -w)
    else()
        target_compile_options(duplicator PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
        )
    endif()
    target_compile_options(duplicator PRIVATE -Og)
endif()

### Constraint Check

find_package(Python3 REQUIRED)

add_test(
        NAME ConstraintCheck
        COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/constraint-check.py
        ${CMAKE_SOURCE_DIR}/test/duplicator.json
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

