/**************************************************************************//**
 *
 * @file student.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Student-specific customizations.
 *
 * The string form of the student ID needs to be placed in the
 *      `.validation.data` section so a stage that requires a string
 *      representation of the student ID cannot simply use a pointer to the
 *      string that will be used to validate the string used in the attack.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include "student.h"

[[gnu::section(".validation.data")]]
char const STUDENT_ID_STRING[] = {
#embed "../customization/student.txt" limit(8)
        , '\0'
};

size_t const STUDENT_ID_SIZE = sizeof(STUDENT_ID_STRING) / sizeof(STUDENT_ID_STRING[0]);    // 9, including the '\0'
