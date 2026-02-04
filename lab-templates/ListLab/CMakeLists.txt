cmake_minimum_required(VERSION 3.10)

project(listlab C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)
option(TIMEOUT "Enable 10-second timeout to prevent runaway code" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(COMMON_SRC
                                    src/list.h                  src/list-test.c         src/list-test.h
        src/sorted-word-entries.c   src/sorted-word-entries.h   src/sorted-test.c       src/sorted-test.h
        src/word-entry.c            src/word-entry.h            src/word-entry-test.c   src/word-entry-test.h
        src/hobbled_alloc.h
)

add_library(arraylist_code STATIC
        ${COMMON_SRC}
        src/array-list.h
        src/array-list.c
)

add_library(linkedlist_code STATIC
        ${COMMON_SRC}
        src/linked-list.h
        src/linked-list.c
)

### Executables

add_executable(arraylist    src/listlab.c)
add_executable(linkedlist   src/listlab.c)

target_link_libraries(arraylist     PRIVATE arraylist_code)
target_link_libraries(linkedlist    PRIVATE linkedlist_code)

if(TIMEOUT)
    target_compile_definitions(arraylist_code  PUBLIC TIMEOUT)
    target_compile_definitions(linkedlist_code PUBLIC TIMEOUT)
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
    endif()
    target_compile_options(arraylist PRIVATE -Og)
    target_compile_options(linkedlist PRIVATE -Og)
endif()

### Unit Tests

function(add_unit_test test_name test_source link_lib)
    add_executable(${test_name} ${test_source} test/unit-tests.h)
    target_link_libraries(${test_name} PRIVATE ${link_lib})
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_unit_test(word_entry_tests                      test/word-entry-tests.c     arraylist_code)
add_unit_test(insertion_sort_with_arraylist_tests   test/insertion-sort-tests.c arraylist_code)
add_unit_test(linkedlist_tests                      test/linkedlist-tests.c     linkedlist_code)
add_unit_test(insertion_sort_with_linkedlist_tests  test/insertion-sort-tests.c linkedlist_code)

### Constraint Check

find_package(Python3 REQUIRED)

add_test(
        NAME ConstraintCheck
        COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/constraint-check.py
        ${CMAKE_SOURCE_DIR}/test/listlab.json
)
