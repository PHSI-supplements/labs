################################################################################
#
# @file caesarcipher-x86-64-linux.s
#
# @author Christopher A. Bohn
#
# @brief Hand-compiled assembly code for the Caesar Cipher in AddressingLab (x86-64, Linux).
#
################################################################################

#
# AddressingLab (c) 2019-26 Christopher A. Bohn
#
# Starter code licensed under the Apache License, Version 2.0
# (http:#www.apache.org/licenses/LICENSE-2.0).
#

    .text

#char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
                                        # rdi: destination
                                        # rsi: text
                                        # edx: key
    .p2align  5
    .global caesar_cipher
    .type   caesar_cipher, %function
caesar_cipher:
    .cfi_startproc
    movl    %edx, %r8d                  # r8d: key
#    char *target = destination;
    movq    %rdi, %r9                   # r9: target
    movzbl  (%rsi), %ecx                # ecx: *text
#    while (*text) {
    testb   %cl, %cl
    je      .Lfunc1endloop
.Lfunc1loop:
#        int reduced_character = *text - 'A';
    subl    $0x41, %ecx                 # ecx: reduced_character
#        if (reduced_character <= 'Z' - 'A') {
    cmpl    $25, %ecx
    ja      .Lfunc1else
#            reduced_character = (reduced_character + key + 26) % 26;
    #leal    26(%rcx, %rdx), %eax   # replaced with distinct steps (like A64) so that we can have a reg-reg instruction
    addl    %r8d, %ecx
    leal    26(%rcx), %eax
    cdq                                 # sign-extend %eax into %edx:%eax
    movl    $26, %ecx
    idivl   %ecx                        # edx: reduced_character
#            *target = (char) (reduced_character + 'A');
    addl    $0x41, %edx
    movb    %dl, (%r9)
    jmp    .Lfunc1endif
#        } else {
.Lfunc1else:
#            *target = *text;
    movb    (%rsi), %cl
    movb    %cl, (%r9)
#        }
.Lfunc1endif:
#        target++;
    incq    %r9
#        text++;
    incq    %rsi
#    }
    movzbl  (%rsi), %ecx                # ecx: *text
    testb   %cl, %cl
    jne     .Lfunc1loop
.Lfunc1endloop:
#    *target = '\0';
    movb    $0, (%r9)
#    return destination;
    movq    %rdi, %rax
    ret
#}
    .cfi_endproc
    .size   caesar_cipher, .-caesar_cipher

#char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
                                        # rdi: destination
                                        # rsi: sentence
    .p2align  5
    .global sentence_to_uppercase
    .type   sentence_to_uppercase, %function
sentence_to_uppercase:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    pushq   %rbx
    .cfi_def_cfa_offset 24
    .cfi_offset 3, -24
    subq    $8, %rsp                    # alignment
    .cfi_def_cfa_offset 32
#    size_t length = strlen(sentence);
    movq    %rsi, %rbx                  # rbx: sentence
    movq    %rdi, %rbp                  # rbp: destination
    movq    %rsi, %rdi
    call    strlen                      # rax: length
#    for (size_t i = 0; i < length; i++) {
    testq   %rax, %rax
    je      .Lfunc2endloop
    mov     $0, %rcx                     # rcx: i
.Lfunc2loop:
#        // destination[i] = (char) toupper(sentence[i]);       # original code
#        destination[i] = (char) upper[(size_t) sentence[i]];   # eliminate a function call
    movzbq  (%rbx, %rcx), %rdx          # rdx: sentence[i]
    #movl    upper(,%rdx, 4), %edx        # edx: upper[sentence[i]]   # replaced with more conventional BIS addressing (mirroring A64)
    leaq    upper, %r8                  # r8: upper
    movl    (%r8, %rdx, 4), %edx        # edx: upper[sentence[i]]
    movb    %dl, (%rbp, %rcx)
#    }
    incq    %rcx
    cmpq    %rax, %rcx
    jb      .Lfunc2loop
.Lfunc2endloop:
#    destination[length] = '\0';
    movb    $0, (%rbp, %rax)
#    return destination;
    movq    %rbp, %rax
    addq    $8, %rsp
    .cfi_def_cfa_offset 24
    popq    %rbx
    .cfi_def_cfa_offset 16
    popq    %rbp
    .cfi_def_cfa_offset 8
    ret
#}
    .cfi_endproc
    .size   sentence_to_uppercase, .-sentence_to_uppercase

#struct cipher_package {
#    char *plaintext;
#    char *ciphertext;
#    int sentence_length;
#    int key;
#};

#bool validate_cipher(struct cipher_package *package) {
                                        # rdi: package
    .p2align  5
    .global validate_cipher
    .type   validate_cipher, %function
validate_cipher:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    pushq   %rbx
    .cfi_def_cfa_offset 24
    .cfi_offset 3, -24
    subq    $264, %rsp                  # buffer: 256 bytes; stack canary: 8 bytes (also alignment)
    .cfi_def_cfa_offset 288
    movq    %rdi, %rbx                  # rbx: package
    # set canary
    movq    %fs:40, %rax
    movq    %rax, 256(%rsp)
    xorl    %eax, %eax
#    bool is_valid = (strlen(package->plaintext) == (size_t) package->sentence_length);
    movq    (%rbx), %rdi                # rdi: package->plaintext
    call    strlen                      # rax: strlen(package->plaintext)
    movslq  16(%rbx), %rdx              # rdx: package->sentence_length
    movq    $0, %rbp                    # rbp: is_valid (initially false)
    cmpq    %rax, %rdx
    jne     .Lfunc3encipher             # if !is_valid, then shortcut the logical AND
#    is_valid = is_valid && (strlen(package->ciphertext) == (size_t) package->sentence_length);
    movq    8(%rbx), %rdi               # rdi: package->ciphertext
    call    strlen                      # rax: strlen(package->ciphertext)
    movslq  16(%rbx), %rdx              # rdx: package->sentence_length
    cmpq    %rax, %rdx
    sete    %bpl
    movzbq  %bpl, %rbp                   # rbp: is_valid = true && (strlen == sentence_length)
.Lfunc3encipher:
#    char deciphered_text[MAXIMUM_INPUT_LENGTH];
#    caesar_cipher(deciphered_text, package->ciphertext, -(package->key));
    leaq    (%rsp), %rdi                # rdi: deciphered_text
    movq    8(%rbx), %rsi               # rsi: package->ciphertext
    movl    20(%rbx), %edx              # edx: package->key
    negl    %edx
    call    caesar_cipher
#    is_valid = is_valid && !strncmp(package->plaintext, deciphered_text, package->sentence_length);
    testq   %rbp, %rbp
    jz      .Lfunc3finished             # if !is_valid, then shortcut the logical AND
    movq    %rax, %rsi                  # rsi: deciphered_text
    movq    (%rbx), %rdi                # rdi: package->plaintext
    movslq  16(%rbx), %rdx              # rdx: package->sentence_length
    call    strncmp
    testl   %eax, %eax
    jz      .Lfunc3finished
    movq    $0, %rbp
.Lfunc3finished:
    # check canary
    movq    256(%rsp), %rdx
    subq    %fs:40, %rdx
    jne     .Lfunc3badcanary
#    return is_valid;
    mov     %rbp, %rax
    addq    $264, %rsp
    .cfi_def_cfa_offset 24
    popq    %rbx
    .cfi_def_cfa_offset 16
    popq    %rbp
    .cfi_def_cfa_offset 8
    ret
.Lfunc3badcanary:
    call    __stack_chk_fail
#}
    .cfi_endproc
    .size   validate_cipher, .-validate_cipher

	.section	.rodata
	.align 32
	.type	upper, @object
	.size	upper, 512
upper:
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	8
	.long	9
	.long	10
	.long	11
	.long	12
	.long	13
	.long	14
	.long	15
	.long	16
	.long	17
	.long	18
	.long	19
	.long	20
	.long	21
	.long	22
	.long	23
	.long	24
	.long	25
	.long	26
	.long	27
	.long	28
	.long	29
	.long	30
	.long	31
	.long	32
	.long	33
	.long	34
	.long	35
	.long	36
	.long	37
	.long	38
	.long	39
	.long	40
	.long	41
	.long	42
	.long	43
	.long	44
	.long	45
	.long	46
	.long	47
	.long	48
	.long	49
	.long	50
	.long	51
	.long	52
	.long	53
	.long	54
	.long	55
	.long	56
	.long	57
	.long	58
	.long	59
	.long	60
	.long	61
	.long	62
	.long	63
	.long	64
	.long	65
	.long	66
	.long	67
	.long	68
	.long	69
	.long	70
	.long	71
	.long	72
	.long	73
	.long	74
	.long	75
	.long	76
	.long	77
	.long	78
	.long	79
	.long	80
	.long	81
	.long	82
	.long	83
	.long	84
	.long	85
	.long	86
	.long	87
	.long	88
	.long	89
	.long	90
	.long	91
	.long	92
	.long	93
	.long	94
	.long	95
	.long	96
	.long	65
	.long	66
	.long	67
	.long	68
	.long	69
	.long	70
	.long	71
	.long	72
	.long	73
	.long	74
	.long	75
	.long	76
	.long	77
	.long	78
	.long	79
	.long	80
	.long	81
	.long	82
	.long	83
	.long	84
	.long	85
	.long	86
	.long	87
	.long	88
	.long	89
	.long	90
	.long	123
	.long	124
	.long	125
	.long	126
	.long	127

    .section        .note.GNU-stack,"",@progbits
