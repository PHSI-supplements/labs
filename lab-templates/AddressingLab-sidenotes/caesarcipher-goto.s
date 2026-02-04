	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_caesar_cipher                  ; -- Begin function caesar_cipher
	.p2align	2
_caesar_cipher:                         ; @caesar_cipher
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	str	x0, [sp, #40]
	str	x1, [sp, #32]
	str	w2, [sp, #28]
	ldr	x8, [sp, #40]
	str	x8, [sp, #16]
	ldr	x8, [sp, #32]
	ldrsb	w8, [x8]
	cbnz	w8, LBB0_2
	b	LBB0_1
LBB0_1:
	b	LBB0_10
LBB0_2:
	b	LBB0_3
LBB0_3:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #32]
	ldrsb	w8, [x8]
	subs	w8, w8, #65
	str	w8, [sp, #12]
	ldr	w8, [sp, #12]
	subs	w8, w8, #25
	b.le	LBB0_5
	b	LBB0_4
LBB0_4:                                 ;   in Loop: Header=BB0_3 Depth=1
	b	LBB0_6
LBB0_5:                                 ;   in Loop: Header=BB0_3 Depth=1
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #28]
	add	w8, w8, w9
	mov	w10, #26                        ; =0x1a
	add	w8, w8, #26
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	str	w8, [sp, #12]
	ldr	w8, [sp, #12]
	add	w8, w8, #65
	ldr	x9, [sp, #16]
	strb	w8, [x9]
	b	LBB0_7
LBB0_6:                                 ;   in Loop: Header=BB0_3 Depth=1
	ldr	x8, [sp, #32]
	ldrb	w8, [x8]
	ldr	x9, [sp, #16]
	strb	w8, [x9]
	b	LBB0_7
LBB0_7:                                 ;   in Loop: Header=BB0_3 Depth=1
	ldr	x8, [sp, #16]
	add	x8, x8, #1
	str	x8, [sp, #16]
	ldr	x8, [sp, #32]
	add	x8, x8, #1
	str	x8, [sp, #32]
	ldr	x8, [sp, #32]
	ldrsb	w8, [x8]
	cbz	w8, LBB0_9
	b	LBB0_8
LBB0_8:                                 ;   in Loop: Header=BB0_3 Depth=1
	b	LBB0_3
LBB0_9:
	b	LBB0_10
LBB0_10:
	ldr	x8, [sp, #16]
	strb	wzr, [x8]
	ldr	x0, [sp, #40]
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_sentence_to_uppercase          ; -- Begin function sentence_to_uppercase
	.p2align	2
_sentence_to_uppercase:                 ; @sentence_to_uppercase
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldr	x0, [sp, #16]
	bl	_strlen
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	cbnz	x8, LBB1_2
	b	LBB1_1
LBB1_1:
	b	LBB1_6
LBB1_2:
	str	xzr, [sp]
	b	LBB1_3
LBB1_3:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]
	ldr	x9, [sp]
	ldrsb	x9, [x8, x9]
	adrp	x8, _upper@PAGE
	add	x8, x8, _upper@PAGEOFF
	ldr	w8, [x8, x9, lsl #2]
	ldur	x9, [x29, #-8]
	ldr	x10, [sp]
	strb	w8, [x9, x10]
	ldr	x8, [sp]
	add	x8, x8, #1
	str	x8, [sp]
	ldr	x8, [sp]
	ldr	x9, [sp, #8]
	subs	x8, x8, x9
	b.hs	LBB1_5
	b	LBB1_4
LBB1_4:                                 ;   in Loop: Header=BB1_3 Depth=1
	b	LBB1_3
LBB1_5:
	b	LBB1_6
LBB1_6:
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #8]
	add	x8, x8, x9
	strb	wzr, [x8]
	ldur	x0, [x29, #-8]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_validate_cipher                ; -- Begin function validate_cipher
	.p2align	2
_validate_cipher:                       ; @validate_cipher
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #320
	stp	x28, x27, [sp, #288]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #304]            ; 16-byte Folded Spill
	add	x29, sp, #304
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-24]
	str	x0, [sp, #16]
	ldr	x8, [sp, #16]
	ldr	x0, [x8]
	bl	_strlen
	ldr	x8, [sp, #16]
	ldrsw	x8, [x8, #16]
	subs	x8, x0, x8
	cset	w8, eq
	strb	w8, [sp, #15]
	ldrb	w8, [sp, #15]
	mov	w9, #0                          ; =0x0
	str	w9, [sp, #8]                    ; 4-byte Folded Spill
	tbz	w8, #0, LBB2_2
	b	LBB2_1
LBB2_1:
	ldr	x8, [sp, #16]
	ldr	x0, [x8, #8]
	bl	_strlen
	ldr	x8, [sp, #16]
	ldrsw	x8, [x8, #16]
	subs	x8, x0, x8
	cset	w8, eq
	str	w8, [sp, #8]                    ; 4-byte Folded Spill
	b	LBB2_2
LBB2_2:
	ldr	w8, [sp, #8]                    ; 4-byte Folded Reload
	mov	w9, #1                          ; =0x1
	and	w8, w8, w9
	strb	w8, [sp, #15]
	ldr	x8, [sp, #16]
	ldr	x1, [x8, #8]
	ldr	x8, [sp, #16]
	ldr	w9, [x8, #20]
	mov	w8, #0                          ; =0x0
	subs	w2, w8, w9
	add	x0, sp, #24
	bl	_caesar_cipher
	ldrb	w8, [sp, #15]
	mov	w9, #0                          ; =0x0
	str	w9, [sp, #4]                    ; 4-byte Folded Spill
	tbz	w8, #0, LBB2_4
	b	LBB2_3
LBB2_3:
	ldr	x8, [sp, #16]
	ldr	x0, [x8]
	ldr	x8, [sp, #16]
	ldrsw	x2, [x8, #16]
	add	x1, sp, #24
	bl	_strncmp
	subs	w8, w0, #0
	cset	w8, eq
	str	w8, [sp, #4]                    ; 4-byte Folded Spill
	b	LBB2_4
LBB2_4:
	ldr	w8, [sp, #4]                    ; 4-byte Folded Reload
	and	w8, w8, #0x1
	strb	w8, [sp, #15]
	ldrb	w8, [sp, #15]
	str	w8, [sp]                        ; 4-byte Folded Spill
	ldur	x9, [x29, #-24]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	b.eq	LBB2_6
	b	LBB2_5
LBB2_5:
	bl	___stack_chk_fail
LBB2_6:
	ldr	w8, [sp]                        ; 4-byte Folded Reload
	and	w0, w8, #0x1
	ldp	x29, x30, [sp, #304]            ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #288]            ; 16-byte Folded Reload
	add	sp, sp, #320
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.p2align	2, 0x0                          ; @upper
_upper:
	.long	0                               ; 0x0
	.long	1                               ; 0x1
	.long	2                               ; 0x2
	.long	3                               ; 0x3
	.long	4                               ; 0x4
	.long	5                               ; 0x5
	.long	6                               ; 0x6
	.long	7                               ; 0x7
	.long	8                               ; 0x8
	.long	9                               ; 0x9
	.long	10                              ; 0xa
	.long	11                              ; 0xb
	.long	12                              ; 0xc
	.long	13                              ; 0xd
	.long	14                              ; 0xe
	.long	15                              ; 0xf
	.long	16                              ; 0x10
	.long	17                              ; 0x11
	.long	18                              ; 0x12
	.long	19                              ; 0x13
	.long	20                              ; 0x14
	.long	21                              ; 0x15
	.long	22                              ; 0x16
	.long	23                              ; 0x17
	.long	24                              ; 0x18
	.long	25                              ; 0x19
	.long	26                              ; 0x1a
	.long	27                              ; 0x1b
	.long	28                              ; 0x1c
	.long	29                              ; 0x1d
	.long	30                              ; 0x1e
	.long	31                              ; 0x1f
	.long	32                              ; 0x20
	.long	33                              ; 0x21
	.long	34                              ; 0x22
	.long	35                              ; 0x23
	.long	36                              ; 0x24
	.long	37                              ; 0x25
	.long	38                              ; 0x26
	.long	39                              ; 0x27
	.long	40                              ; 0x28
	.long	41                              ; 0x29
	.long	42                              ; 0x2a
	.long	43                              ; 0x2b
	.long	44                              ; 0x2c
	.long	45                              ; 0x2d
	.long	46                              ; 0x2e
	.long	47                              ; 0x2f
	.long	48                              ; 0x30
	.long	49                              ; 0x31
	.long	50                              ; 0x32
	.long	51                              ; 0x33
	.long	52                              ; 0x34
	.long	53                              ; 0x35
	.long	54                              ; 0x36
	.long	55                              ; 0x37
	.long	56                              ; 0x38
	.long	57                              ; 0x39
	.long	58                              ; 0x3a
	.long	59                              ; 0x3b
	.long	60                              ; 0x3c
	.long	61                              ; 0x3d
	.long	62                              ; 0x3e
	.long	63                              ; 0x3f
	.long	64                              ; 0x40
	.long	65                              ; 0x41
	.long	66                              ; 0x42
	.long	67                              ; 0x43
	.long	68                              ; 0x44
	.long	69                              ; 0x45
	.long	70                              ; 0x46
	.long	71                              ; 0x47
	.long	72                              ; 0x48
	.long	73                              ; 0x49
	.long	74                              ; 0x4a
	.long	75                              ; 0x4b
	.long	76                              ; 0x4c
	.long	77                              ; 0x4d
	.long	78                              ; 0x4e
	.long	79                              ; 0x4f
	.long	80                              ; 0x50
	.long	81                              ; 0x51
	.long	82                              ; 0x52
	.long	83                              ; 0x53
	.long	84                              ; 0x54
	.long	85                              ; 0x55
	.long	86                              ; 0x56
	.long	87                              ; 0x57
	.long	88                              ; 0x58
	.long	89                              ; 0x59
	.long	90                              ; 0x5a
	.long	91                              ; 0x5b
	.long	92                              ; 0x5c
	.long	93                              ; 0x5d
	.long	94                              ; 0x5e
	.long	95                              ; 0x5f
	.long	96                              ; 0x60
	.long	65                              ; 0x41
	.long	66                              ; 0x42
	.long	67                              ; 0x43
	.long	68                              ; 0x44
	.long	69                              ; 0x45
	.long	70                              ; 0x46
	.long	71                              ; 0x47
	.long	72                              ; 0x48
	.long	73                              ; 0x49
	.long	74                              ; 0x4a
	.long	75                              ; 0x4b
	.long	76                              ; 0x4c
	.long	77                              ; 0x4d
	.long	78                              ; 0x4e
	.long	79                              ; 0x4f
	.long	80                              ; 0x50
	.long	81                              ; 0x51
	.long	82                              ; 0x52
	.long	83                              ; 0x53
	.long	84                              ; 0x54
	.long	85                              ; 0x55
	.long	86                              ; 0x56
	.long	87                              ; 0x57
	.long	88                              ; 0x58
	.long	89                              ; 0x59
	.long	90                              ; 0x5a
	.long	123                             ; 0x7b
	.long	124                             ; 0x7c
	.long	125                             ; 0x7d
	.long	126                             ; 0x7e
	.long	127                             ; 0x7f

.subsections_via_symbols
