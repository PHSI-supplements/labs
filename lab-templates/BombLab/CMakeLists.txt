cmake_minimum_required(VERSION 3.10)

project(bomblab C ASM)

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
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(ARCH x86-64)
    set(BOMB_SOURCE "${CMAKE_SOURCE_DIR}/lib/bomb-x86-64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(ARCH A64)
    set(BOMB_SOURCE "${CMAKE_SOURCE_DIR}/lib/bomb-A64")
else()
    message(FATAL_ERROR "Unsupported processor architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

### Message for Students

message(STATUS "")
message(STATUS "================ Assembly file selection ================")
message(STATUS "Processor Architecture: ${ARCH}")
message(STATUS "Operating System:       ${OS}")
message(STATUS "Bomb:                   build/bomb")
message(STATUS "=========================================================")
message(STATUS "")

### Copy the appropriate bomb

configure_file("${BOMB_SOURCE}" "${CMAKE_BINARY_DIR}/bomb" COPYONLY)
file(CHMOD "${CMAKE_BINARY_DIR}/bomb"
        PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
)

### Report Environment

set(META_SRC "${CMAKE_CURRENT_LIST_DIR}/submission_metadata.json")
set(META_TMP "${CMAKE_BINARY_DIR}/submission_metadata.json")

# Only substitute if the placeholders are still present
file(READ "${META_SRC}" META_CONTENTS)
if(META_CONTENTS MATCHES "@ARCH@" OR META_CONTENTS MATCHES "@OS@")
    configure_file("${META_SRC}" "${META_TMP}" @ONLY)
    file(COPY_FILE "${META_TMP}" "${META_SRC}")
endif()
