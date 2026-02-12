////////////////////////////////////////////////////////////////////////////////
//
// @file caesarcipher-A64-linux.s
//
// @author (TYPE YOUR NAME HERE)
//
// @brief Code for the Caesar Cipher in AddressingLab (A64, Linux).
//
////////////////////////////////////////////////////////////////////////////////

//
// AddressingLab assignment and starter code (c) 2019-26 Christopher A. Bohn
// AddressingLab solution (c) the above-named student
//

// TODO: test this implementation

    .arch armv8-a
    .text

//char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
                                        // x0: destination
                                        // x1: text
                                        // w2: key
    .align  2
    .global caesar_cipher
    .type   caesar_cipher, %function
caesar_cipher:
    .cfi_startproc
//    char *target = destination;
///// PLACE INSTRUCTION FOR TASK 1 ON NEXT LINE /////

                                        // x10: target
    ldrb    w11, [x1]                   // w11: *text
//    while (*text) {
    cbz     w11, .Lfunc1endloop
.Lfunc1loop:
//        int reduced_character = *text - 'A';
///// PLACE INSTRUCTION FOR TASK 2 ON NEXT LINE /////

                                        // w12: reduced_character
//        if ((unsigned char) reduced_character <= 'Z' - 'A') {
    and     w13, w12, #0xFF
    cmp     w13, #25
    bhi     .Lfunc1else
//            reduced_character = (reduced_character + key + 26) % 26;
///// PLACE INSTRUCTION FOR TASK 3 ON NEXT LINE /////

    add     w12, w12, #26
    mov     w14, #26
    sdiv    w13, w12, w14
    msub    w12, w13, w14, w12
//            *target = (char) (reduced_character + 'A');
    add     w13, w12, #0x41
///// PLACE INSTRUCTION FOR TASK 4 ON NEXT LINE /////

    b       .Lfunc1endif
//        } else {
.Lfunc1else:
//            *target = *text;
    strb    w11, [x10]
//        }
.Lfunc1endif:
//        target++;
    add     x10, x10, #1
//        text++;
    add     x1, x1, #1
//    }
///// PLACE INSTRUCTION FOR TASK 5 ON NEXT LINE /////

                                        # w11: *text
    cbnz    w11, .Lfunc1loop
.Lfunc1endloop:
//    *target = '\0';
    strb    wzr, [x10]
//    return destination;
    ret
//}
    .cfi_endproc
    .size   caesar_cipher, .-caesar_cipher

//char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
                                        // x0: destination
                                        // x1: sentence
    .align  2
    .global sentence_to_uppercase
    .type   sentence_to_uppercase, %function
sentence_to_uppercase:
    .cfi_startproc
    stp     x29, x30, [sp, #-32]!
    .cfi_def_cfa_offset 32
    .cfi_offset x29, -32
    .cfi_offset x30, -24
    mov     x29, sp
    stp     x20, x21, [sp, 16]
    .cfi_offset x20, -16
    .cfi_offset x21, -8
//    size_t length = strlen(sentence);
    mov     x21, x1                     // x21: sentence
    mov     x20, x0                     // x20: destination
    mov     x0, x1
    bl      strlen                     // x0: length
//    for (size_t i = 0// i < length// i++) {
    cbz     x0, .Lfunc2endloop
    mov     x10, #0                     // x10: i
.Lfunc2loop:
//        destination[i] = (char) upper[(size_t) sentence[i]];
///// PLACE INSTRUCTION FOR TASK 6 ON NEXT LINE /////

                                        // w11: sentence[i]
    adrp    x12, .LANCHOR0
    add     x12, x12, :lo12:.LANCHOR0   // x12: upper
///// PLACE INSTRUCTION FOR TASK 7 ON NEXT LINE /////

                                        // w12: upper[sentence[i]]
///// PLACE INSTRUCTION FOR TASK 8 ON NEXT LINE /////

//    }
    add     x10, x10, #1
    cmp     x10, x0
    blo     .Lfunc2loop
.Lfunc2endloop:
//    destination[length] = '\0';
    strb    wzr, [x20, x0]
//    return destination;
    mov     x0, x20
    ldp     x20, x21, [sp, 16]
    ldp     x29, x30, [sp], 32
    .cfi_restore 30
    .cfi_restore 29
    .cfi_restore 20
    .cfi_restore 21
    .cfi_def_cfa_offset 0
    ret
//}
    .cfi_endproc
    .size   sentence_to_uppercase, .-sentence_to_uppercase

//struct cipher_package {
//    char *plaintext;
//    char *ciphertext;
//    int sentence_length;
//    int key;
//};

//bool validate_cipher(struct cipher_package *package) {
                                        // x0: package
    .align  2
    .global validate_cipher
    .type   validate_cipher, %function
validate_cipher:
    .cfi_startproc
    sub     sp, sp, #304                // buffer: 256 bytes; saved registers: 32 bytes; stack canary: 8 bytes; alignment: 8 bytes
    .cfi_def_cfa_offset 304
    stp     fp, lr, [sp, 272]
    .cfi_offset x29, -32
    .cfi_offset x30, -24
    add     fp, sp, 272
    stp     x20, x21, [sp, 288]
    .cfi_offset x20, -16
    .cfi_offset x21, -8
    mov     x20, x0                     // x20: package
    // set canary
    adrp    x10, __stack_chk_guard
    ldr     x10, [x10, #:lo12:__stack_chk_guard]
    ldr     x10, [x10]
///// PLACE INSTRUCTION FOR TASK 9 ON NEXT LINE /////

    mov     x10, #0
//    bool is_valid = (strlen(package->plaintext) == (size_t) package->sentence_length);
    ldr     x0, [x20]                   // x0: package->plaintext
    bl      strlen                      // x0: strlen(package->plaintext)
    ldrsw   x21, [x20, #16]             // x21: package->sentence_length
    mov     x10, #0                     // w10: is_valid (initially false)
    cmp     x0, x21
    bne     .Lfunc3encipher             // if !is_valid, then shortcut the logical AND
//    is_valid = is_valid && (strlen(package->ciphertext) == (size_t) package->sentence_length);
///// PLACE INSTRUCTION FOR TASK 10 ON NEXT LINE /////

                                        // x0: package->ciphertext
    bl      strlen                      // x0: strlen(package->ciphertext)
    cmp     x0, x21
    cset    x10, eq                     // x10: is_valid = true && (strlen == sentence_length)
.Lfunc3encipher:
//    char deciphered_text[MAXIMUM_INPUT_LENGTH];
//    caesar_cipher(deciphered_text, package->ciphertext, -(package->key));
    add     x0, sp, #8                  // x0: deciphered_text
    ldr     x1, [x20, #8]               // x1: package->ciphertext
    ldr     w2, [x20, #20]              // w2 = package->key
    neg     w2, w2
    mov     x21, x10                    // x21: is_valid
    bl      caesar_cipher
//    is_valid = is_valid && !strncmp(package->plaintext, deciphered_text, package->sentence_length);
    cbz     x21, .Lfunc3finished        // if !is_valid, then shortcut the logical AND
    mov     x1, x0                      // x1: deciphered_text
    ldr     x0, [x20]                   // x0: package->plaintext
    ldrsw   x2, [x20, #16]              // x2: package->sentence_length
    bl       strncmp
    cbz     w0, .Lfunc3finished
    mov     x21, #0
.Lfunc3finished:
    // check canary
    ldr     x11, [fp, #-40]
    adrp    x10, __stack_chk_guard
    ldr x10, [x10, #:lo12:__stack_chk_guard]
    ldr x10, [x10]
    cmp     x10, x11
    bne     .Lfunc3badcanary
//    return is_valid;
    mov     x0, x21
    ldp     x20, x21, [sp, 288]
    ldp     fp, lr, [sp, 272]
    add     sp, sp, #304
    .cfi_restore 20
    .cfi_restore 21
    .cfi_restore 29
    .cfi_restore 30
    .cfi_def_cfa_offset 0
    ret
.Lfunc3badcanary:
    bl      __stack_chk_fail
//}
    .cfi_endproc
    .size   validate_cipher, .-validate_cipher

    .section        .rodata
    .align  3
    .set    .LANCHOR0,. + 0
    .type   upper, %object
    .size   upper, 512
upper:
    .word   0
    .word   1
    .word   2
    .word   3
    .word   4
    .word   5
    .word   6
    .word   7
    .word   8
    .word   9
    .word   10
    .word   11
    .word   12
    .word   13
    .word   14
    .word   15
    .word   16
    .word   17
    .word   18
    .word   19
    .word   20
    .word   21
    .word   22
    .word   23
    .word   24
    .word   25
    .word   26
    .word   27
    .word   28
    .word   29
    .word   30
    .word   31
    .word   32
    .word   33
    .word   34
    .word   35
    .word   36
    .word   37
    .word   38
    .word   39
    .word   40
    .word   41
    .word   42
    .word   43
    .word   44
    .word   45
    .word   46
    .word   47
    .word   48
    .word   49
    .word   50
    .word   51
    .word   52
    .word   53
    .word   54
    .word   55
    .word   56
    .word   57
    .word   58
    .word   59
    .word   60
    .word   61
    .word   62
    .word   63
    .word   64
    .word   65
    .word   66
    .word   67
    .word   68
    .word   69
    .word   70
    .word   71
    .word   72
    .word   73
    .word   74
    .word   75
    .word   76
    .word   77
    .word   78
    .word   79
    .word   80
    .word   81
    .word   82
    .word   83
    .word   84
    .word   85
    .word   86
    .word   87
    .word   88
    .word   89
    .word   90
    .word   91
    .word   92
    .word   93
    .word   94
    .word   95
    .word   96
    .word   65
    .word   66
    .word   67
    .word   68
    .word   69
    .word   70
    .word   71
    .word   72
    .word   73
    .word   74
    .word   75
    .word   76
    .word   77
    .word   78
    .word   79
    .word   80
    .word   81
    .word   82
    .word   83
    .word   84
    .word   85
    .word   86
    .word   87
    .word   88
    .word   89
    .word   90
    .word   123
    .word   124
    .word   125
    .word   126
    .word   127

    .section        .note.GNU-stack,"",@progbits
