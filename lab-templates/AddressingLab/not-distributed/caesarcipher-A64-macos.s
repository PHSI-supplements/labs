;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; @file caesarcipher-A64-macos.s
;
; @author (TYPE YOUR NAME HERE)
;
; @brief Code for the Caesar Cipher in AddressingLab (A64, macOS).
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; AddressingLab assignment and starter code (c) 2019-26 Christopher A. Bohn
; AddressingLab solution (c) the above-named student
;

    .section    __TEXT,__text,regular,pure_instructions
    .build_version macos, 15, 0 sdk_version 26, 2

;char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
                                        ; x0: destination
                                        ; x1: text
                                        ; w2: key
    .globl  _caesar_cipher
    .p2align    2
_caesar_cipher:
    .cfi_startproc
;    char *target = destination;
;;;;; PLACE INSTRUCTION FOR TASK 1 ON NEXT LINE ;;;;;

                                        ; x10: target
    ldrb    w11, [x1]                   ; w11: *text
;    while (*text) {
    cbz     w11, Lfunc1endloop
Lfunc1loop:
;        int reduced_character = *text - 'A';
;;;;; PLACE INSTRUCTION FOR TASK 2 ON NEXT LINE ;;;;;

                                        ; w12: reduced_character
;        if ((unsigned char) reduced_character <= 'Z' - 'A') {
    and     w13, w12, #0xFF
    cmp     w13, #25
    bhi     Lfunc1else
;            reduced_character = (reduced_character + key + 26) % 26;
;;;;; PLACE INSTRUCTION FOR TASK 3 ON NEXT LINE ;;;;;

    add     w12, w12, #26
    mov     w14, #26
    sdiv    w13, w12, w14
    msub    w12, w13, w14, w12
;            *target = (char) (reduced_character + 'A');
    add     w13, w12, #0x41
;;;;; PLACE INSTRUCTION FOR TASK 4 ON NEXT LINE ;;;;;

    b       Lfunc1endif
;        } else {
Lfunc1else:
;            *target = *text;
    strb    w11, [x10]
;        }
Lfunc1endif:
;        target++;
    add     x10, x10, #1
;        text++;
    add     x1, x1, #1
;    }
;;;;; PLACE INSTRUCTION FOR TASK 5 ON NEXT LINE ;;;;;

                                        ; w11: *text
    cbnz    w11, Lfunc1loop
Lfunc1endloop:
;    *target = '\0';
    strb    wzr, [x10]
;    return destination;
    ret
;}
    .cfi_endproc

;char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
                                        ; x0: destination
                                        ; x1: sentence
    .globl  _sentence_to_uppercase
    .p2align    2
_sentence_to_uppercase:
    .cfi_startproc
    stp     x29, x30, [sp, #-32]!
    .cfi_def_cfa sp, 32
    .cfi_offset x29, -32
    .cfi_offset x30, -24
    mov     x29, sp
    stp     x20, x21, [sp, 16]
    .cfi_offset x20, -16
    .cfi_offset x21, -8
;    size_t length = strlen(sentence);
    mov     x21, x1                     ; x21: sentence
    mov     x20, x0                     ; x20: destination
    mov     x0, x1
    bl      _strlen                     ; x0: length
;    for (size_t i = 0; i < length; i++) {
    cbz     x0, Lfunc2endloop
    mov     x10, #0                     ; x10: i
Lfunc2loop:
;        destination[i] = (char) upper[(size_t) sentence[i]];
;;;;; PLACE INSTRUCTION FOR TASK 6 ON NEXT LINE ;;;;;

                                        ; w11: sentence[i]
    adrp    x12, _upper@PAGE
    add     x12, x12, _upper@PAGEOFF    ; x12: upper
;;;;; PLACE INSTRUCTION FOR TASK 7 ON NEXT LINE ;;;;;

                                        ; w12: upper[sentence[i]]
;;;;; PLACE INSTRUCTION FOR TASK 8 ON NEXT LINE ;;;;;

;    }
    add     x10, x10, #1
    cmp     x10, x0
    blo     Lfunc2loop
Lfunc2endloop:
;    destination[length] = '\0';
    strb    wzr, [x20, x0]
;    return destination;
    mov     x0, x20
    ldp     x20, x21, [sp, 16]
    ldp     x29, x30, [sp], 32
    ret
;}
    .cfi_endproc

;struct cipher_package {
;    char *plaintext;
;    char *ciphertext;
;    int sentence_length;
;    int key;
;};

;bool validate_cipher(struct cipher_package *package) {
                                        ; x0: package
    .globl  _validate_cipher
    .p2align    2
_validate_cipher:
    .cfi_startproc
    sub     sp, sp, #304                ; buffer: 256 bytes; saved registers: 32 bytes; stack canary: 8 bytes; alignment: 8 bytes
    .cfi_def_cfa_offset 304
    stp     fp, lr, [sp, 272]
    .cfi_offset x29, -32
    .cfi_offset x30, -24
    add     fp, sp, 272
    stp     x20, x21, [sp, 288]
    .cfi_offset x20, -16
    .cfi_offset x21, -8
    mov     x20, x0                     ; x20: package
    ; set canary
    adrp    x10, ___stack_chk_guard@GOTPAGE
    ldr     x10, [x10, ___stack_chk_guard@GOTPAGEOFF]
    ldr     x10, [x10]
;;;;; PLACE INSTRUCTION FOR TASK 9 ON NEXT LINE ;;;;;

    mov     x10, #0
;    bool is_valid = (strlen(package->plaintext) == (size_t) package->sentence_length);
    ldr     x0, [x20]                   ; x0: package->plaintext
    bl      _strlen                     ; x0: strlen(package->plaintext)
    ldrsw   x21, [x20, #16]             ; x21: package->sentence_length
    mov     x10, #0                     ; w10: is_valid (initially false)
    cmp     x0, x21
    bne     Lfunc3encipher              ; if !is_valid, then shortcut the logical AND
;    is_valid = is_valid && (strlen(package->ciphertext) == (size_t) package->sentence_length);
;;;;; PLACE INSTRUCTION FOR TASK 10 ON NEXT LINE ;;;;;

                                        ; x0: package->ciphertext
    bl      _strlen                     ; x0: strlen(package->ciphertext)
    cmp     x0, x21
    cset    x10, eq                     ; x10: is_valid = true && (strlen == sentence_length)
Lfunc3encipher:
;    char deciphered_text[MAXIMUM_INPUT_LENGTH];
;    caesar_cipher(deciphered_text, package->ciphertext, -(package->key));
    add     x0, sp, #8                  ; x0: deciphered_text
    ldr     x1, [x20, #8]               ; x1: package->ciphertext
    ldr     w2, [x20, #20]              ; w2 = package->key
    neg     w2, w2
    mov     x21, x10                    ; x21: is_valid
    bl      _caesar_cipher
;    is_valid = is_valid && !strncmp(package->plaintext, deciphered_text, package->sentence_length);
    cbz     x21, Lfunc3finished         ; if !is_valid, then shortcut the logical AND
    mov     x1, x0                      ; x1: deciphered_text
    ldr     x0, [x20]                   ; x0: package->plaintext
    ldrsw   x2, [x20, #16]              ; x2: package->sentence_length
    bl      _strncmp
    cbz     w0, Lfunc3finished
    mov     x21, #0
Lfunc3finished:
    ; check canary
    ldr     x11, [fp, #-40]
    adrp    x10, ___stack_chk_guard@GOTPAGE
    ldr     x10, [x10, ___stack_chk_guard@GOTPAGEOFF]
    ldr     x10, [x10]
    cmp     x10, x11
    bne     Lfunc3badcanary
;    return is_valid;
    mov     x0, x21
    ldp     x20, x21, [sp, 288]
    ldp     fp, lr, [sp, 272]
    add     sp, sp, #304
    ret
Lfunc3badcanary:
    bl      ___stack_chk_fail
;}
    .cfi_endproc

    .section    __TEXT,__const
    .p2align        2, 0x0
_upper:
     .long   0
     .long   1
     .long   2
     .long   3
     .long   4
     .long   5
     .long   6
     .long   7
     .long   8
     .long   9
     .long   10
     .long   11
     .long   12
     .long   13
     .long   14
     .long   15
     .long   16
     .long   17
     .long   18
     .long   19
     .long   20
     .long   21
     .long   22
     .long   23
     .long   24
     .long   25
     .long   26
     .long   27
     .long   28
     .long   29
     .long   30
     .long   31
     .long   32
     .long   33
     .long   34
     .long   35
     .long   36
     .long   37
     .long   38
     .long   39
     .long   40
     .long   41
     .long   42
     .long   43
     .long   44
     .long   45
     .long   46
     .long   47
     .long   48
     .long   49
     .long   50
     .long   51
     .long   52
     .long   53
     .long   54
     .long   55
     .long   56
     .long   57
     .long   58
     .long   59
     .long   60
     .long   61
     .long   62
     .long   63
     .long   64
     .long   65
     .long   66
     .long   67
     .long   68
     .long   69
     .long   70
     .long   71
     .long   72
     .long   73
     .long   74
     .long   75
     .long   76
     .long   77
     .long   78
     .long   79
     .long   80
     .long   81
     .long   82
     .long   83
     .long   84
     .long   85
     .long   86
     .long   87
     .long   88
     .long   89
     .long   90
     .long   91
     .long   92
     .long   93
     .long   94
     .long   95
     .long   96
     .long   65
     .long   66
     .long   67
     .long   68
     .long   69
     .long   70
     .long   71
     .long   72
     .long   73
     .long   74
     .long   75
     .long   76
     .long   77
     .long   78
     .long   79
     .long   80
     .long   81
     .long   82
     .long   83
     .long   84
     .long   85
     .long   86
     .long   87
     .long   88
     .long   89
     .long   90
     .long   123
     .long   124
     .long   125
     .long   126
     .long   127

.subsections_via_symbols
