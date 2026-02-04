        .file   "example.c"
        .text
        .globl  caesar_cipher
        .type   caesar_cipher, @function
caesar_cipher:
        .cfi_startproc
        movq    %rdi, %r9
        movq    %rsi, %rcx
        movq    %rdi, %rsi
        jmp     .L2
        .p2align 5
.L3:
        movb    %al, (%rsi)
.L4:
        addq    $1, %rsi
        addq    $1, %rcx
.L2:
        movzbl  (%rcx), %eax
        testb   %al, %al
        je      .L6
        leal    -65(%rax), %edi
        cmpb    $25, %dil
        ja      .L3
        movsbl  %al, %eax
        leal    -39(%rax,%rdx), %edi
        movslq  %edi, %rax
        imulq   $1321528399, %rax, %rax
        sarq    $35, %rax
        movl    %edi, %r8d
        sarl    $31, %r8d
        subl    %r8d, %eax
        imull   $26, %eax, %r8d
        movl    %edi, %eax
        subl    %r8d, %eax
        addl    $65, %eax
        movb    %al, (%rsi)
        jmp     .L4
.L6:
        movb    $0, (%rsi)
        movq    %r9, %rax
        ret
        .cfi_endproc
        .size   caesar_cipher, .-caesar_cipher
        .globl  sentence_to_uppercase
        .type   sentence_to_uppercase, @function
sentence_to_uppercase:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        pushq   %rbx
        .cfi_def_cfa_offset 24
        .cfi_offset 3, -24
        subq    $8, %rsp
        .cfi_def_cfa_offset 32
        movq    %rdi, %rbx
        movq    %rsi, %rbp
        movq    %rsi, %rdi
        call    strlen
        movl    $0, %edx
        jmp     .L8
        .p2align 5
.L9:
        movsbq  0(%rbp,%rdx), %rcx
        movzbl  upper(%rcx), %ecx
        movb    %cl, (%rbx,%rdx)
        addq    $1, %rdx
.L8:
        cmpq    %rax, %rdx
        jb      .L9
        movb    $0, (%rbx,%rax)
        movq    %rbx, %rax
        addq    $8, %rsp
        .cfi_def_cfa_offset 24
        popq    %rbx
        .cfi_def_cfa_offset 16
        popq    %rbp
        .cfi_def_cfa_offset 8
        ret
        .cfi_endproc
        .size   sentence_to_uppercase, .-sentence_to_uppercase
        .globl  validate_cipher
        .type   validate_cipher, @function
validate_cipher:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        pushq   %rbx
        .cfi_def_cfa_offset 24
        .cfi_offset 3, -24
        subq    $280, %rsp
        .cfi_def_cfa_offset 304
        movq    %rdi, %rbx
        movq    %fs:40, %rax
        movq    %rax, 264(%rsp)
        xorl    %eax, %eax
        movq    (%rdi), %rdi
        call    strlen
        movslq  16(%rbx), %rbp
        cmpq    %rbp, %rax
        je      .L20
        movl    $0, %ebp
.L12:
        andl    $1, %ebp
        movq    8(%rbx), %rsi
        movl    20(%rbx), %edx
        negl    %edx
        movq    %rsp, %rdi
        call    caesar_cipher
        testb   %bpl, %bpl
        je      .L17
        movq    (%rbx), %rdi
        movslq  16(%rbx), %rdx
        movq    %rsp, %rsi
        call    strncmp
        testl   %eax, %eax
        je      .L18
        movl    $0, %eax
        jmp     .L13
.L20:
        movq    8(%rbx), %rdi
        call    strlen
        cmpq    %rax, %rbp
        je      .L16
        movl    $0, %ebp
        jmp     .L12
.L16:
        movl    $1, %ebp
        jmp     .L12
.L17:
        movl    $0, %eax
.L13:
        andl    $1, %eax
        movq    264(%rsp), %rdx
        subq    %fs:40, %rdx
        jne     .L21
        addq    $280, %rsp
        .cfi_remember_state
        .cfi_def_cfa_offset 24
        popq    %rbx
        .cfi_def_cfa_offset 16
        popq    %rbp
        .cfi_def_cfa_offset 8
        ret
.L18:
        .cfi_restore_state
        movl    $1, %eax
        jmp     .L13
.L21:
        call    __stack_chk_fail
        .cfi_endproc
        .size   validate_cipher, .-validate_cipher
        .section        .rodata
        .align 32
        .type   upper, @object
        .size   upper, 128
upper:
        .base64 "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlae3x9fn8="
        .ident  "GCC: (Compiler-Explorer-Build-gcc--binutils-2.44) 15.2.0"
        .section        .note.GNU-stack,"",@progbits