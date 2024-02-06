#                       #
# DO NOT EDIT THIS FILE #
#                       #

###############################################################################
#
# @file authoritative_x86_64_windows.asm
#
# @author Christopher A. Bohn
#
# @brief Implementation of arithmetic authoritative results, written in x86_64
#       assembly for Windows
#
# The code within the functions was hand-written; however, the surrounding
#       directives were prepared by a compiler.
#
###############################################################################

#
# IntegerLab (c) 2018-24 Christopher A. Bohn
#
# Starter code licensed under the Apache License, Version 2.0
# (http://www.apache.org/licenses/LICENSE-2.0).
#

#include "authoritative_results.h"

#if defined X86_64_WINDOWS

	.file	"authoritative_results.c"
	.text
	.globl	evaluate_addition
	.def	evaluate_addition;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_addition
evaluate_addition:
	.seh_endprologue
    addw %dx, %di
    setz 4(%r8)
    sets 5(%r8)
    seto 6(%r8)
    setc 7(%r8)
    movw %di, (%r8)
	ret
	.seh_endproc
	.globl	evaluate_subtraction
	.def	evaluate_subtraction;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_subtraction
evaluate_subtraction:
	.seh_endprologue
    subw %dx, %di
    setz 4(%r8)
    sets 5(%r8)
    seto 6(%r8)
    setc 7(%r8)
    movw %di, (%r8)
	ret
	.seh_endproc
	.globl	evaluate_unsigned_multiplication
	.def	evaluate_unsigned_multiplication;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_unsigned_multiplication
evaluate_unsigned_multiplication:
	.seh_endprologue
	pushq %rax
	pushq %rdx
	movw %di, %ax
	mulw %dx
	movw %dx, %di
	popq %rdx
	setz 4(%r8)
	sets 5(%r8)
	seto 6(%r8)
	setc 7(%r8)
	movw %ax, (%r8)
	movw %di, 2(%r8)
	popq %rax
	ret
	.seh_endproc
	.globl	evaluate_unsigned_division
	.def	evaluate_unsigned_division;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_unsigned_division
evaluate_unsigned_division:
	.seh_endprologue
	pushq %rax
	pushq %rdx
	movw %di, %ax
	movw $0, %dx
	divw %dx
	movw %dx, %di
	popq %rdx
	setz 4(%r8)
	sets 5(%r8)
	seto 6(%r8)
	setc 7(%r8)
	movw %ax, (%r8)
	movw %di, 2(%r8)
	popq %rax
	ret
	.seh_endproc
	.globl	evaluate_signed_multiplication
	.def	evaluate_signed_multiplication;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_signed_multiplication
evaluate_signed_multiplication:
	.seh_endprologue
	pushq %rax
	pushq %rdx
	movw %di, %ax
	imulw %dx
	movw %dx, %di
	popq %rdx
	setz 4(%r8)
	sets 5(%r8)
	seto 6(%r8)
	setc 7(%r8)
	movw %ax, (%r8)
	movw %di, 2(%r8)
	popq %rax
	ret
	.seh_endproc
	.globl	evaluate_signed_division
	.def	evaluate_signed_division;	.scl	2;	.type	32;	.endef
	.seh_proc	evaluate_signed_division
evaluate_signed_division:
	.seh_endprologue
	pushq %rax
	pushq %rdx
	movw %di, %ax
	movw $0, %dx
	testw %ax, %ax
	# cmovs $-1, %r8
	# the next two instructions substitute for the cmov instruction, which cannot move from immediate to register
	jns .Lcmovsubstitute
	movw $-1, %dx
.Lcmovsubstitute:
	# the previous two instructions substitute for the cmov instruction
	idivw %dx
	movw %dx, %di
	popq %rdx
	setz 4(%r8)
	sets 5(%r8)
	seto 6(%r8)
	setc 7(%r8)
	movw %ax, (%r8)
	movw %di, 2(%r8)
	popq %rax
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 4.9.2"

#endif