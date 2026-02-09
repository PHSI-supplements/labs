cmake_minimum_required(VERSION 3.10)

project(addressinglab C ASM)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INSTRUCTOR_BUILD "Suppress warnings for grading" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS linux)
elseif(APPLE)
    set(OS macos)
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(ARCH x86-64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(ARCH A64)
else()
    message(FATAL_ERROR "Unsupported processor architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(asm_file src/caesarcipher-${ARCH}-${OS}.s)

### Message for Students

message(STATUS "")
message(STATUS "================ Assembly file selection ================")
message(STATUS "Processor Architecture: ${ARCH}")
message(STATUS "Operating System:       ${OS}")
message(STATUS "EDIT THIS FILE: ${CMAKE_CURRENT_LIST_DIR}/${asm_file}")
message(STATUS "=========================================================")
message(STATUS "")

### Report Environment

set(META_SRC "${CMAKE_CURRENT_LIST_DIR}/submission_metadata.json")
set(META_TMP "${CMAKE_BINARY_DIR}/submission_metadata.json")

# Only substitute if the placeholders are still present
file(READ "${META_SRC}" META_CONTENTS)
if(META_CONTENTS MATCHES "@ARCH@" OR META_CONTENTS MATCHES "@OS@")
    configure_file("${META_SRC}" "${META_TMP}" @ONLY)
    file(COPY_FILE "${META_TMP}" "${META_SRC}")
endif()

### Executables

add_executable(addressinglab src/addressinglab.c ${asm_file})

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

### Unit Tests

file (GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)

foreach (test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} test/unit-tests.h ${asm_file})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()
