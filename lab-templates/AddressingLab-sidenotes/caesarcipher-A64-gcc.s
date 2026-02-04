        .arch armv8-a
        .file   "example.c"
        .text
        .align  2
        .global caesar_cipher
        .type   caesar_cipher, %function
caesar_cipher:
        .cfi_startproc
        mov     x5, x0
        b       .L2
.L3:
        strb    w3, [x5]
.L4:
        add     x5, x5, 1
        add     x1, x1, 1
.L2:
        ldrb    w3, [x1]
        cbz     w3, .L6
        sub     w4, w3, #65
        and     w4, w4, 255
        cmp     w4, 25
        bhi     .L3
        sub     w3, w3, #65
        add     w3, w3, w2
        add     w3, w3, 26
        mov     w6, 26
        sdiv    w4, w3, w6
        msub    w3, w4, w6, w3
        add     w3, w3, 65
        strb    w3, [x5]
        b       .L4
.L6:
        strb    wzr, [x5]
        ret
        .cfi_endproc
        .size   caesar_cipher, .-caesar_cipher
        .align  2
        .global sentence_to_uppercase
        .type   sentence_to_uppercase, %function
sentence_to_uppercase:
        .cfi_startproc
        stp     x29, x30, [sp, -32]!
        .cfi_def_cfa_offset 32
        .cfi_offset 29, -32
        .cfi_offset 30, -24
        mov     x29, sp
        stp     x19, x20, [sp, 16]
        .cfi_offset 19, -16
        .cfi_offset 20, -8
        mov     x19, x0
        mov     x20, x1
        mov     x0, x1
        bl      strlen
        mov     x2, 0
        b       .L8
.L9:
        ldrb    w4, [x20, x2]
        adrp    x3, .LANCHOR0
        add     x3, x3, :lo12:.LANCHOR0
        ldrb    w3, [x3, w4, sxtw]
        strb    w3, [x19, x2]
        add     x2, x2, 1
.L8:
        cmp     x2, x0
        bcc     .L9
        strb    wzr, [x19, x0]
        mov     x0, x19
        ldp     x19, x20, [sp, 16]
        ldp     x29, x30, [sp], 32
        .cfi_restore 30
        .cfi_restore 29
        .cfi_restore 19
        .cfi_restore 20
        .cfi_def_cfa_offset 0
        ret
        .cfi_endproc
        .size   sentence_to_uppercase, .-sentence_to_uppercase
        .align  2
        .global validate_cipher
        .type   validate_cipher, %function
validate_cipher:
        .cfi_startproc
        sub     sp, sp, #304
        .cfi_def_cfa_offset 304
        stp     x29, x30, [sp, 272]
        .cfi_offset 29, -32
        .cfi_offset 30, -24
        add     x29, sp, 272
        stp     x19, x20, [sp, 288]
        .cfi_offset 19, -16
        .cfi_offset 20, -8
        mov     x19, x0
        adrp    x0, __stack_chk_guard
        ldr     x1, [x0, #:lo12:__stack_chk_guard]
        str     x1, [sp, 264]
        mov     x1, 0
        ldr     x0, [x19]
        bl      strlen
        ldrsw   x20, [x19, 16]
        cmp     x0, x20
        beq     .L20
        mov     w20, 0
.L12:
        ldr     w2, [x19, 20]
        neg     w2, w2
        ldr     x1, [x19, 8]
        add     x0, sp, 8
        bl      caesar_cipher
        tbz     x20, 0, .L17
        ldrsw   x2, [x19, 16]
        add     x1, sp, 8
        ldr     x0, [x19]
        bl      strncmp
        cbz     w0, .L18
        mov     w0, 0
        b       .L13
.L20:
        ldr     x0, [x19, 8]
        bl      strlen
        cmp     x20, x0
        beq     .L16
        mov     w20, 0
        b       .L12
.L16:
        mov     w20, 1
        b       .L12
.L17:
        mov     w0, 0
.L13:
        adrp    x1, __stack_chk_guard
        ldr     x3, [sp, 264]
        ldr     x2, [x1, #:lo12:__stack_chk_guard]
        subs    x3, x3, x2
        mov     x2, 0
        bne     .L21
        ldp     x29, x30, [sp, 272]
        ldp     x19, x20, [sp, 288]
        add     sp, sp, 304
        .cfi_remember_state
        .cfi_restore 19
        .cfi_restore 20
        .cfi_restore 29
        .cfi_restore 30
        .cfi_def_cfa_offset 0
        ret
.L18:
        .cfi_restore_state
        mov     w0, 1
        b       .L13
.L21:
        bl      __stack_chk_fail
        .cfi_endproc
        .size   validate_cipher, .-validate_cipher
        .section        .rodata
        .align  3
        .set    .LANCHOR0,. + 0
        .type   upper, %object
        .size   upper, 128
upper:
        .base64 "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlae3x9fn8="
        .ident  "GCC: (GNU) 15.2.0"
        .section        .note.GNU-stack,"",@progbits