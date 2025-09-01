cmake_minimum_required(VERSION 3.10)

project(listlab C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)
option(TIMEOUT "Enable 10-second timeout to prevent runaway code" ON)

### Executables

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(COMMON_SRC
        src/listlab.c               src/list-test.c
        src/sorted_word_entries.c   src/sorted-test.c
        src/word-entry.c            src/word-entry-test.c
)
set(ARRAYLIST_SRC src/array-list.c)
set(LINKEDLIST_SRC src/linked-list.c)
file(GLOB HDR_FILES CONFIGURE_DEPENDS src/*.h)      # some IDEs need this

add_executable(arraylist    ${COMMON_SRC}   ${ARRAYLIST_SRC}    ${HDR_FILES})
add_executable(linkedlist   ${COMMON_SRC}   ${LINKEDLIST_SRC}   ${HDR_FILES})

if(TIMEOUT)
    target_compile_definitions(arraylist PRIVATE TIMEOUT)
    target_compile_definitions(linkedlist PRIVATE TIMEOUT)
endif()

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(arraylist PRIVATE -w)
        target_compile_options(linkedlist PRIVATE -w)
    else()
        target_compile_options(arraylist PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
        )
        target_compile_options(linkedlist PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
        )
        # I'd like to replace -Wno-unused-parameter with [[maybe_unused]] exactly where it's needed, but there are 23 temporarily-unused parameters!
    endif()
    target_compile_options(arraylist PRIVATE -Og)
    target_compile_options(linkedlist PRIVATE -Og)
endif()

### Constraint Check

find_package(Python3 REQUIRED)

add_test(
        NAME ConstraintCheck
        COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/constraint-check.py
        ${CMAKE_SOURCE_DIR}/test/listlab.json
)
