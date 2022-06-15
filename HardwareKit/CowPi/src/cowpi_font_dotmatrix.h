/**************************************************************************//**
 *
 * @file cowpi_font_dotmatrix.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Provides a font to display printable ASCII characters on dot-matrix
 *      displays.
 *
 * All characters are guaranteed to occupy a rectangle no greater than 8 rows
 * by 5 columns.
 *
 * @todo    Move these functions into a separate file; it looks like the fonts
 *      are only copied to flash memory if they're actually used, and add
 *      cowpi_font.h to the headers #included by CowPi.h.
 *
 * @todo    Test `cowpi_string_to_vertical_dotmatrix`.
 *
 ******************************************************************************/

/* CowPi (c) 2021-22 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COWPI_FONT_DOTMATRIX_H
#define COWPI_FONT_DOTMATRIX_H

#include <stdint.h>
#include <avr/pgmspace.h>

const uint8_t cowpi_fuzz[8]         PROGMEM = {0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A};

const uint8_t cowpi_space[8]        PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_bang[8]         PROGMEM = {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00};
const uint8_t cowpi_doublequote[8]  PROGMEM = {0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_octothorpe[8]   PROGMEM = {0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00};
const uint8_t cowpi_dollar[8]       PROGMEM = {0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04, 0x00};
const uint8_t cowpi_percent[8]      PROGMEM = {0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00};
const uint8_t cowpi_ampersand[8]    PROGMEM = {0x0C, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0D, 0x00};
const uint8_t cowpi_apostrophe[8]   PROGMEM = {0x03, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_leftparen[8]    PROGMEM = {0x01, 0x02, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00};
const uint8_t cowpi_rightparen[8]   PROGMEM = {0x04, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 0x00};
const uint8_t cowpi_asterisk[8]     PROGMEM = {0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00, 0x00};
const uint8_t cowpi_plus[8]         PROGMEM = {0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00};
const uint8_t cowpi_comma[8]        PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x02};
const uint8_t cowpi_dash[8]         PROGMEM = {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_period[8]       PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00};
const uint8_t cowpi_slash[8]        PROGMEM = {0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00};

const uint8_t cowpi_zero[8]         PROGMEM = {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E, 0x00};
const uint8_t cowpi_one[8]          PROGMEM = {0x02, 0x06, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_two[8]          PROGMEM = {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F, 0x00};
const uint8_t cowpi_three[8]        PROGMEM = {0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_four[8]         PROGMEM = {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02, 0x00};
const uint8_t cowpi_five[8]         PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_six[8]          PROGMEM = {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_seven[8]        PROGMEM = {0x1F, 0x11, 0x01, 0x02, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_eight[8]        PROGMEM = {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_nine[8]         PROGMEM = {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C, 0x00};
const uint8_t cowpi_colon[8]        PROGMEM = {0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00};
const uint8_t cowpi_semicolon[8]    PROGMEM = {0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x01, 0x02};
const uint8_t cowpi_lessthan[8]     PROGMEM = {0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00};
const uint8_t cowpi_equals[8]       PROGMEM = {0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00};
const uint8_t cowpi_greaterthan[8]  PROGMEM = {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00};
const uint8_t cowpi_question[8]     PROGMEM = {0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04, 0x00};

const uint8_t cowpi_at[8]           PROGMEM = {0x0E, 0x11, 0x15, 0x1B, 0x1F, 0x10, 0x0E, 0x00};
const uint8_t cowpi_upper_A[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_upper_B[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E, 0x00};
const uint8_t cowpi_upper_C[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E, 0x00};
const uint8_t cowpi_upper_D[8]      PROGMEM = {0x1C, 0x13, 0x11, 0x11, 0x11, 0x13, 0x1C, 0x00};
const uint8_t cowpi_upper_E[8]      PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F, 0x00};
const uint8_t cowpi_upper_F[8]      PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_upper_G[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F, 0x00};
const uint8_t cowpi_upper_H[8]      PROGMEM = {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_upper_I[8]      PROGMEM = {0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_upper_J[8]      PROGMEM = {0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C, 0x00};
const uint8_t cowpi_upper_K[8]      PROGMEM = {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00};
const uint8_t cowpi_upper_L[8]      PROGMEM = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00};
const uint8_t cowpi_upper_M[8]      PROGMEM = {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_upper_N[8]      PROGMEM = {0x11, 0x19, 0x19, 0x15, 0x13, 0x13, 0x11, 0x00};
const uint8_t cowpi_upper_O[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00};

const uint8_t cowpi_upper_P[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_upper_Q[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D, 0x00};
const uint8_t cowpi_upper_R[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x00};
const uint8_t cowpi_upper_S[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_upper_T[8]      PROGMEM = {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_upper_U[8]      PROGMEM = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_upper_V[8]      PROGMEM = {0x11, 0x11, 0x11, 0x0A, 0x0A, 0x0A, 0x04, 0x00};
const uint8_t cowpi_upper_W[8]      PROGMEM = {0x11, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x0A, 0x00};
const uint8_t cowpi_upper_X[8]      PROGMEM = {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00};
const uint8_t cowpi_upper_Y[8]      PROGMEM = {0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_upper_Z[8]      PROGMEM = {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F, 0x00};
const uint8_t cowpi_leftbracket[8]  PROGMEM = {0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00};
const uint8_t cowpi_backslash[8]    PROGMEM = {0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x00};
const uint8_t cowpi_rightbracket[8] PROGMEM = {0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x00};
const uint8_t cowpi_carat[8]        PROGMEM = {0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_underscore[8]   PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00};

const uint8_t cowpi_backtick[8]     PROGMEM = {0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_lower_a[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x01, 0x0E, 0x11, 0x0E, 0x00};
const uint8_t cowpi_lower_b[8]      PROGMEM = {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1E, 0x00};
const uint8_t cowpi_lower_c[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E, 0x00};
const uint8_t cowpi_lower_d[8]      PROGMEM = {0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x0F, 0x00};
const uint8_t cowpi_lower_e[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00};
const uint8_t cowpi_lower_f[8]      PROGMEM = {0x06, 0x09, 0x08, 0x1C, 0x08, 0x08, 0x08, 0x00};
const uint8_t cowpi_lower_g[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x0F, 0x01, 0x11, 0x0E};
const uint8_t cowpi_lower_h[8]      PROGMEM = {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_lower_i[8]      PROGMEM = {0x00, 0x02, 0x00, 0x06, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_lower_j[8]      PROGMEM = {0x00, 0x02, 0x00, 0x06, 0x02, 0x02, 0x09, 0x06};
const uint8_t cowpi_lower_k[8]      PROGMEM = {0x08, 0x08, 0x09, 0x0A, 0x0C, 0x0A, 0x09, 0x00};
const uint8_t cowpi_lower_l[8]      PROGMEM = {0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_lower_m[8]      PROGMEM = {0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15, 0x00};
const uint8_t cowpi_lower_n[8]      PROGMEM = {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_lower_o[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00};

const uint8_t cowpi_lower_p[8]      PROGMEM = {0x00, 0x00, 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10};
const uint8_t cowpi_lower_q[8]      PROGMEM = {0x00, 0x00, 0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01};
const uint8_t cowpi_lower_r[8]      PROGMEM = {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_lower_s[8]      PROGMEM = {0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E, 0x00};
const uint8_t cowpi_lower_t[8]      PROGMEM = {0x00, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x03, 0x00};
const uint8_t cowpi_lower_u[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D, 0x00};
const uint8_t cowpi_lower_v[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00};
const uint8_t cowpi_lower_w[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00};
const uint8_t cowpi_lower_x[8]      PROGMEM = {0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00};
const uint8_t cowpi_lower_y[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x09, 0x07, 0x01, 0x0E};
const uint8_t cowpi_lower_z[8]      PROGMEM = {0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00};
const uint8_t cowpi_leftbrace[8]    PROGMEM = {0x01, 0x02, 0x02, 0x04, 0x02, 0x02, 0x01, 0x00};
const uint8_t cowpi_pipe[8]         PROGMEM = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00};
const uint8_t cowpi_rightbrace[8]   PROGMEM = {0x04, 0x02, 0x02, 0x01, 0x02, 0x02, 0x04, 0x00};
const uint8_t cowpi_tilde[8]        PROGMEM = {0x00, 0x00, 0x0D, 0x12, 0x00, 0x00, 0x00, 0x00};

const int8_t cowpi_font_dotmatrix_widths[] PROGMEM = {
        5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        2, 1, 3, 5, 5, 5, 5, 2, 3, 3, 5, 5, 2, 5, 2, 5,
        5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 4, 5, 4, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 5, 3, 5, 5,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 4, 4, 3, 5, 5, 5,

        5, 5, 5, 5, 4, 5, 5, 5, 5, 5, 5, 3, 1, 3, 5, 5
};

const uint8_t *const cowpi_font_dotmatrix[] PROGMEM = {
        cowpi_zero, cowpi_one, cowpi_two, cowpi_three, cowpi_four, cowpi_five, cowpi_six, cowpi_seven,
        cowpi_eight, cowpi_nine, cowpi_upper_A, cowpi_upper_B, cowpi_upper_C, cowpi_upper_D, cowpi_upper_E, cowpi_upper_F,
        cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz,
        cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz, cowpi_fuzz,
        cowpi_space, cowpi_bang, cowpi_doublequote, cowpi_octothorpe, cowpi_dollar, cowpi_percent, cowpi_ampersand,
        cowpi_apostrophe, cowpi_leftparen, cowpi_rightparen, cowpi_asterisk, cowpi_plus, cowpi_comma, cowpi_dash, cowpi_period, cowpi_slash,
        cowpi_zero, cowpi_one, cowpi_two, cowpi_three, cowpi_four, cowpi_five, cowpi_six, cowpi_seven,
        cowpi_eight, cowpi_nine, cowpi_colon, cowpi_semicolon, cowpi_lessthan, cowpi_equals, cowpi_greaterthan, cowpi_question,
        cowpi_at, cowpi_upper_A, cowpi_upper_B, cowpi_upper_C, cowpi_upper_D, cowpi_upper_E, cowpi_upper_F, cowpi_upper_G,
        cowpi_upper_H, cowpi_upper_I, cowpi_upper_J, cowpi_upper_K, cowpi_upper_L, cowpi_upper_M, cowpi_upper_N, cowpi_upper_O,
        cowpi_upper_P, cowpi_upper_Q, cowpi_upper_R, cowpi_upper_S, cowpi_upper_T, cowpi_upper_U, cowpi_upper_V,cowpi_upper_W,
        cowpi_upper_X, cowpi_upper_Y, cowpi_upper_Z, cowpi_leftbracket, cowpi_backslash, cowpi_rightbracket, cowpi_carat, cowpi_underscore,
        cowpi_backtick, cowpi_lower_a, cowpi_lower_b, cowpi_lower_c, cowpi_lower_d, cowpi_lower_e, cowpi_lower_f, cowpi_lower_g,
        cowpi_lower_h, cowpi_lower_i, cowpi_lower_j, cowpi_lower_k, cowpi_lower_l, cowpi_lower_m, cowpi_lower_n, cowpi_lower_o,
        cowpi_lower_p, cowpi_lower_q, cowpi_lower_r, cowpi_lower_s, cowpi_lower_t, cowpi_lower_u, cowpi_lower_v, cowpi_lower_w,
        cowpi_lower_x, cowpi_lower_y, cowpi_lower_z, cowpi_leftbrace, cowpi_pipe, cowpi_rightbrace, cowpi_tilde, cowpi_fuzz
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides the number of columns needed to represent a character in the
 *      dot matrix font.
 *
 * @param   c the character whose width is to be determined
 * @return  the dot matrix width of the character
 */
inline int8_t cowpi_get_dotmatrix_width(char c) __attribute__((__always_inline__));
inline int8_t cowpi_get_dotmatrix_width(char c) {
    return pgm_read_byte(cowpi_font_dotmatrix_widths + c);
}

/**
 * @brief Provides the dot matrix representation of an ASCII character with no
 *      blank columns to the right of the character.
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character. Each
 * bit position in an array element represents a column.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_ascii_to_5wide_dotmatrix
 * @sa cowpi_ascii_to_8wide_dotmatrix
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
inline uint8_t *cowpi_ascii_to_narrow_dotmatrix(uint8_t *destination, char c) __attribute__((__always_inline__));
inline uint8_t *cowpi_ascii_to_narrow_dotmatrix(uint8_t *destination, char c) {
    memcpy_P(destination, (const uint8_t *)pgm_read_word(cowpi_font_dotmatrix + c), 8);
    return destination;
}

/**
 * @brief Provides the dot matrix representation of an ASCII character centered
 *      horizontally in the five columns used for a 5x8 dot matrix character
 *      (the five right-most columns of the 8x8 matrix).
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_ascii_to_narrow_dotmatrix
 * @sa cowpi_ascii_to_8wide_dotmatrix
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
inline uint8_t *cowpi_ascii_to_5wide_dotmatrix(uint8_t *destination, char c) __attribute__((__always_inline__));
inline uint8_t *cowpi_ascii_to_5wide_dotmatrix(uint8_t *destination, char c) {
    destination = cowpi_ascii_to_narrow_dotmatrix(destination, c);
    for (int i = 0; i < 8; i++) {
        destination[i] <<= (5 - cowpi_get_dotmatrix_width(c) + 1) / 2;
    }
    return destination;
}

/**
 * @brief Provides the dot matrix representation of an ASCII character centered
 *      horizontally in the eight columns of the 8x8 matrix.
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_ascii_to_narrow_dotmatrix
 * @sa cowpi_ascii_to_5wide_dotmatrix
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
inline uint8_t *cowpi_ascii_to_8wide_dotmatrix(uint8_t *destination, char c) __attribute__((__always_inline__));
inline uint8_t *cowpi_ascii_to_8wide_dotmatrix(uint8_t *destination, char c) {
    destination = cowpi_ascii_to_5wide_dotmatrix(destination, c);
    for (int i = 0; i < 8; i++) {
        destination[i] <<= 1;
    }
    return destination;
}

/**
 * @brief Transposes an 8x8 dot matrix representation.
 *
 * After the transposition, each element of the `matrix` array represents a
 * column, and each bit position of an array element represents a row.
 *
 * This is an in-place transposition; that is, the original matrix is
 * overwritten.
 *
 * @param matrix    the dot matrix to be transposed
 * @return          `matrix` after the transposition
 */
inline uint8_t *cowpi_transpose_dotmatrix(uint8_t *matrix) {
    uint8_t new_matrix[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 7; i >= 0; i--) {
        uint8_t original_row = matrix[i];
        for (int j = 7; j >= 0; j--) {
            new_matrix[j] |= original_row & 0x1;
            original_row >>= 1;
            if (i > 0) {
                new_matrix[j] <<= 1;
            }
        }
    }
    memcpy(matrix, new_matrix, 8);
    return matrix;
}

/**
 * @brief Provides a single dot matrix representation of an ASCII character
 *      string suitable for scrolling horizontally.
 *
 * Each byte of the destination array stores one column of the string's dot
 * matrix representation, with element 0 being the leftmost column of the first
 * character.
 *
 * The `destination` array is assumed to point to a block of memory with
 * sufficient space allocated to hold the full string's dot matrix
 * representation; `6 * strlen(s)` is guaranteed to be sufficient.
 *
 * @param destination   an empty array to hold the dot matrix representation
 * @param s             the ASCII string whose dot matrix representation is to
 *      be provided
 * @param kerned        indicates whether to use minimal space between
 *      characters or to use a fixed 5 columns per character
 * @return              the number of columns in the string's dot matrix
 *      representation
 */
inline int cowpi_string_to_horizontal_dotmatrix(uint8_t *destination, const char *s, bool kerned) {
    uint8_t letter[8];
    int length = 0;
    while (*s) {
        if (kerned) {
            if (*s == ' ') {
                char last_character = *(s - 1);
                destination[length++] = 0x00;
                destination[length++] = 0x00;
                if (last_character == '.' || last_character == '!' || last_character == '?' || last_character == ':') {
                    destination[length++] = 0x00;
                    destination[length++] = 0x00;
                }
            } else {
                cowpi_transpose_dotmatrix(cowpi_ascii_to_narrow_dotmatrix(letter, *s));
                for (int i = 0; i < 8; i++) {
                    if (letter[i]) {
                        destination[length++] = letter[i];
                    }
                }
            }
        } else {
            cowpi_transpose_dotmatrix(cowpi_ascii_to_5wide_dotmatrix(letter, *s));
            for (int i = 3; i < 8; i++) {
                destination[length++] = letter[i];
            }
        }
        s++;
        destination[length++] = 0x00;
    }
    return length;
}

/**
 * @brief Provides a single dot matrix representation of an ASCII character
 *      string suitable for scrolling vertically.
 *
 * Each byte of the destination array stores one row of the string's dot matrix
 * representation, with element 0 being the top row of the first character.
 *
 * The `destination` array is assumed to point to a block of memory with
 * sufficient space allocated to hold the full string's dot matrix
 * representation; `6 * strlen(s)` is guaranteed to be sufficient.
 *
 * @param destination   an empty array to hold the dot matrix representation
 * @param s             the ASCII string whose dot matrix representation is to
 *      be provided
 * @param kerned        indicates whether to use minimal space between
 *      characters or to use a fixed 8 rows per character
 * @return              the number of rows in the string's dot matrix
 *      representation
 */
inline int cowpi_string_to_vertical_dotmatrix(uint8_t *destination, const char *s, bool kerned) {
    uint8_t letter[8];
    int length = 0;
    while (*s) {
        cowpi_ascii_to_8wide_dotmatrix(letter, *s);
        if (kerned && (*s == ' ')) {
            char last_character = *(s - 1);
            destination[length++] = 0x00;
            destination[length++] = 0x00;
            if (last_character == '.' || last_character == '!' || last_character == '?' || last_character == ':') {
                destination[length++] = 0x00;
                destination[length++] = 0x00;
            }
        } else {
            for (int i = 0; i < 8; i++) {
                if (!kerned || letter[i]) {
                    destination[length++] = letter[i];
                }
            }
        }
        s++;
        destination[length++] = 0x00;
    }
    return length;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_FONT_DOTMATRIX_H
