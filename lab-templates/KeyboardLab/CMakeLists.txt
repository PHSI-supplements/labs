cmake_minimum_required(VERSION 3.10)

project(keyboardlab C)

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

add_executable(keyboardlab ${SRC_FILES} ${HDR_FILES})

target_link_libraries(keyboardlab PRIVATE m)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    if (INSTRUCTOR_BUILD)
        target_compile_options(keyboardlab PRIVATE -w)
    else()
        target_compile_options(keyboardlab PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -Wno-unused-value       # The starter code has two "statements with no effect"
        )
    endif()
    target_compile_options(keyboardlab PRIVATE -Og)
endif()

### Constraint Check

find_package(Python3 REQUIRED)

foreach(lab keyboardlab1.json keyboardlab2.json keyboardlab3.json)
    get_filename_component(name ${lab} NAME_WE)
    add_test(
            NAME ConstraintCheck_${name}
            COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/test/constraint-check.py
            ${CMAKE_SOURCE_DIR}/test/${lab}
    )
    set_tests_properties(ConstraintCheck_${name} PROPERTIES LABELS constraints)
endforeach()
