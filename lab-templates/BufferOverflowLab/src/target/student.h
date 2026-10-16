/**************************************************************************//**
 *
 * @file student.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Extern variable declarations student data.
 *
 * The student ID will change from one student to the next; however, the
 *      variable names and helper macros are fixed and do not need to be
 *      customized. The contents of this file do are the aspects of the string
 *      form of the student ID that do not change.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>
#include <stdint.h>

extern char const STUDENT_ID_STRING[];      //!< String representation of the student ID
extern size_t const STUDENT_ID_SIZE;        //!< The size of the string representation of the student ID


#define HAS_0A_BYTE(number) (                           \
    (((uint32_t)(number) >>  0) & 0xFFu) == 0x0Au ||    \
    (((uint32_t)(number) >>  8) & 0xFFu) == 0x0Au ||    \
    (((uint32_t)(number) >> 16) & 0xFFu) == 0x0Au ||    \
    (((uint32_t)(number) >> 24) & 0xFFu) == 0x0Au       )

#define RECTIFIED_STUDENT_ID_INT(raw_student_id) (                              \
    !HAS_0A_BYTE(raw_student_id)        ? (uint32_t)(raw_student_id)        :   \
    !HAS_0A_BYTE((raw_student_id) << 1) ? (uint32_t)((raw_student_id) << 1) :   \
    !HAS_0A_BYTE((raw_student_id) >> 1) ? (uint32_t)((raw_student_id) >> 1) :   \
    !HAS_0A_BYTE((raw_student_id) << 2) ? (uint32_t)((raw_student_id) << 2) :   \
                                          (uint32_t)((raw_student_id) >> 2)     )

constexpr uint8_t DIGITS[] = {
#embed "../customization/student.txt"
};

/* GCC doesn't yet recognize that DIGITS[0] is an integer constant expression
constexpr uint32_t RAW_STUDENT_ID =
        (DIGITS[0] - '0') * 10000000u   +
        (DIGITS[1] - '0') * 1000000u    +
        (DIGITS[2] - '0') * 100000u     +
        (DIGITS[3] - '0') * 10000u      +
        (DIGITS[4] - '0') * 1000u       +
        (DIGITS[5] - '0') * 100u        +
        (DIGITS[6] - '0') * 10u         +
        (DIGITS[7] - '0') * 1u          ;

constexpr uint32_t STUDENT_ID_INT = RECTIFIED_STUDENT_ID_INT(RAW_STUDENT_ID);   //!< Integer representation of the student ID
*/

/* Fortunately, GCC tends to treat static const variables as compile-time constants during code generation */
static uint32_t const RAW_STUDENT_ID =
        (DIGITS[0] - '0') * 10000000u   +
        (DIGITS[1] - '0') * 1000000u    +
        (DIGITS[2] - '0') * 100000u     +
        (DIGITS[3] - '0') * 10000u      +
        (DIGITS[4] - '0') * 1000u       +
        (DIGITS[5] - '0') * 100u        +
        (DIGITS[6] - '0') * 10u         +
        (DIGITS[7] - '0') * 1u          ;

static uint32_t const STUDENT_ID_INT = RECTIFIED_STUDENT_ID_INT(RAW_STUDENT_ID);   //!< Integer representation of the student ID


#endif //STUDENT_H
