cmake_minimum_required(VERSION 3.10)

project(buffer-overflow-lab C)


# RANDOMIZATION

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(STUDENT_ID_FILE "${CMAKE_SOURCE_DIR}/src/customization/student.txt")
set(RANDOMIZATION_H "${CMAKE_SOURCE_DIR}/src/customization/randomization.h")
set(RANDOMIZATION_GEN "${CMAKE_SOURCE_DIR}/src/customization/generate_randomization.py")

add_custom_command(
        OUTPUT  "${RANDOMIZATION_H}"
        COMMAND "${Python3_EXECUTABLE}" "${RANDOMIZATION_GEN}" "${STUDENT_ID_FILE}" "${RANDOMIZATION_H}"
        DEPENDS "${RANDOMIZATION_GEN}" "${STUDENT_ID_FILE}"
        COMMENT "Generating student-specific randomization.h from student-id.txt"
        VERBATIM
)

#add_custom_target(generate_randomization_header DEPENDS "${RANDOMIZATION_H}")


# BACK TO YOUR REGULARLY-SCHEDULED PROJECT BUILD

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()


## Determine the operating environment

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


## Do the build

file(GLOB STANDARD_SRC_FILES CONFIGURE_DEPENDS src/target/*.c)
file(GLOB STANDARD_HDR_FILES CONFIGURE_DEPENDS src/target/*.h)
file(GLOB CUSTOM_SRC_FILES CONFIGURE_DEPENDS src/customization/*.c)
file(GLOB CUSTOM_HDR_FILES CONFIGURE_DEPENDS src/customization/*.h)

add_executable(target ${STANDARD_SRC_FILES} ${STANDARD_HDR_FILES} ${CUSTOM_SRC_FILES} ${CUSTOM_HDR_FILES}
#        src/class/pretty-printer.c
#        src/class/pretty-printer.h
)
target_sources(target PRIVATE "${RANDOMIZATION_H}")
add_executable(hex2raw src/hex2raw/hex2raw.c)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(target PRIVATE
            -Og
            -Wall
            -Wextra
            -fstack-protector   # but we'll disable this for the vulnerable function
            -fno-pie
            -DCHECKPOINTS_SIZE=12288
            -DGADGETS_SIZE=4096
            -DVALIDATION_CODE_SIZE=65536
            -DVALIDATION_DATA_SIZE=256
            -D_FORTIFY_SOURCE=0
    )
    target_link_options(target PRIVATE
            -no-pie
            -Wl,--section-start=.checkpoints.text=0x1009C000    # 12KB for the functions students need to execute
            -Wl,--section-start=.gadgets.text=0x1009F000        # 4KB for the ROP gadgets
            -Wl,--defsym=__gadgets_start=0x1009F000
            -Wl,--section-start=.validation.text=0x100A0000     # Up to 64KB of code with 0x0A in the address for validation code
            -Wl,--section-start=.validation.data=0x20010A00     # 256B for data with 0x0A in the address, in the address range for the RP2040 heap
            # TODO: consider using a section to allocate space for the stack
            # TODO: the object used in the heap overflow stages probably ought to be in an arena section so that we can set execute/no-execute permissions
    )
endif()
