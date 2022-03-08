	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.file	1 "/Users/cabohn/personal-version-control/phsi_supplements/labs/03.integerlab/starter-code" "./alu.h"
	.file	2 "/Users/cabohn/personal-version-control/phsi_supplements/labs/03.integerlab/starter-code" "/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/_types/_uint16_t.h"
	.globl	_add                    ## -- Begin function add
	.p2align	4, 0x90
_add:                                   ## @add
Lfunc_begin0:
	.file	3 "/Users/cabohn/personal-version-control/phsi_supplements/labs/03.integerlab/starter-code" "alu.c"
	.loc	3 21 0                  ## alu.c:21:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: add:augend <- $edi
	##DEBUG_VALUE: add:augend <- $edi
	##DEBUG_VALUE: add:addend <- $esi
	##DEBUG_VALUE: add:addend <- $esi
Ltmp0:
	.loc	3 23 30 prologue_end    ## alu.c:23:30
	addl	%esi, %edi
Ltmp1:
	##DEBUG_VALUE: add:addition <- [DW_OP_LLVM_fragment 16 8] 0
	.loc	3 25 5                  ## alu.c:25:5
	movzwl	%di, %eax
Ltmp2:
	##DEBUG_VALUE: add:addition <- [DW_OP_LLVM_fragment 0 16] $eax
	popq	%rbp
	retq
Ltmp3:
Lfunc_end0:
	.cfi_endproc
                                        ## -- End function
	.globl	_subtract               ## -- Begin function subtract
	.p2align	4, 0x90
_subtract:                              ## @subtract
Lfunc_begin1:
	.loc	3 31 0                  ## alu.c:31:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: subtract:menuend <- $edi
	##DEBUG_VALUE: subtract:menuend <- $edi
	##DEBUG_VALUE: subtract:subtrahend <- $esi
	##DEBUG_VALUE: subtract:subtrahend <- $esi
Ltmp4:
	##DEBUG_VALUE: subtract:augend <- $edi
	##DEBUG_VALUE: subtract:augend <- $edi
	.loc	3 33 34 prologue_end    ## alu.c:33:34
	negl	%esi
Ltmp5:
	.loc	3 34 12                 ## alu.c:34:12
	movzwl	%si, %esi
Ltmp6:
	##DEBUG_VALUE: subtract:addend <- $esi
	##DEBUG_VALUE: subtract:augend <- $edi
	##DEBUG_VALUE: subtract:menuend <- $edi
	popq	%rbp
	jmp	_add                    ## TAILCALL
Ltmp7:
Lfunc_end1:
	.cfi_endproc
                                        ## -- End function
	.globl	_multiply               ## -- Begin function multiply
	.p2align	4, 0x90
_multiply:                              ## @multiply
Lfunc_begin2:
	.loc	3 41 0                  ## alu.c:41:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: multiply:multiplicand <- $edi
	##DEBUG_VALUE: multiply:multiplier <- $esi
                                        ## kill: def $edi killed $edi def $rdi
Ltmp8:
	##DEBUG_VALUE: multiply:multiplication <- [DW_OP_LLVM_fragment 64 8] 0
	##DEBUG_VALUE: multiply:multiplier <- $esi
	##DEBUG_VALUE: multiply:multiplicand <- $edi
	.loc	3 43 43 prologue_end    ## alu.c:43:43
	imull	%esi, %edi
Ltmp9:
	.loc	3 46 5                  ## alu.c:46:5
	movzwl	%di, %eax
	shlq	$32, %rdi
	orq	%rdi, %rax
	xorl	%edx, %edx
	popq	%rbp
	retq
Ltmp10:
Lfunc_end2:
	.cfi_endproc
                                        ## -- End function
	.globl	_divide                 ## -- Begin function divide
	.p2align	4, 0x90
_divide:                                ## @divide
Lfunc_begin3:
	.loc	3 53 0                  ## alu.c:53:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: divide:dividend <- $edi
	##DEBUG_VALUE: divide:dividend <- $edi
	##DEBUG_VALUE: divide:divisor <- $esi
	##DEBUG_VALUE: divide:divisor <- $esi
Ltmp11:
	##DEBUG_VALUE: divide:divisor <- $si
	.loc	3 55 9 prologue_end     ## alu.c:55:9
	testw	%si, %si
Ltmp12:
	.loc	3 55 9 is_stmt 0        ## alu.c:55:9
	je	LBB3_1
## %bb.2:
	##DEBUG_VALUE: divide:divisor <- $si
	##DEBUG_VALUE: divide:dividend <- $edi
Ltmp13:
	##DEBUG_VALUE: divide:dividend <- $di
	.loc	3 57 39 is_stmt 1       ## alu.c:57:39
	xorl	%edx, %edx
	movl	%edi, %eax
	divw	%si
                                        ## kill: def $dx killed $dx def $rdx
	.loc	3 58 5                  ## alu.c:58:5
	shll	$16, %edx
	movzwl	%ax, %eax
	jmp	LBB3_3
Ltmp14:
LBB3_1:
	##DEBUG_VALUE: divide:divisor <- $si
	##DEBUG_VALUE: divide:dividend <- $edi
	.loc	3 0 5 is_stmt 0         ## alu.c:0:5
	xorl	%eax, %eax
	xorl	%edx, %edx
LBB3_3:
	##DEBUG_VALUE: divide:divisor <- $si
Ltmp15:
	##DEBUG_VALUE: divide:division <- [DW_OP_LLVM_fragment 32 8] 0
	.loc	3 60 5 is_stmt 1        ## alu.c:60:5
	orq	%rdx, %rax
	popq	%rbp
	retq
Ltmp16:
Lfunc_end3:
	.cfi_endproc
                                        ## -- End function
	.comm	_is_signed,1,0          ## @is_signed
	.file	4 "/Users/cabohn/personal-version-control/phsi_supplements/labs/03.integerlab/starter-code" "/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/_types/_uint32_t.h"
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple LLVM version 10.0.1 (clang-1001.0.46.4)" ## string offset=0
	.asciz	"alu.c"                 ## string offset=46
	.asciz	"/Users/cabohn/personal-version-control/phsi_supplements/labs/03.integerlab/starter-code" ## string offset=52
	.asciz	"is_signed"             ## string offset=140
	.asciz	"_Bool"                 ## string offset=150
	.asciz	"uint16_t"              ## string offset=156
	.asciz	"unsigned short"        ## string offset=165
	.asciz	"add"                   ## string offset=180
	.asciz	"subtract"              ## string offset=184
	.asciz	"multiply"              ## string offset=193
	.asciz	"divide"                ## string offset=202
	.asciz	"addition_subtraction_result" ## string offset=209
	.asciz	"result"                ## string offset=237
	.asciz	"overflow"              ## string offset=244
	.asciz	"multiplication_result" ## string offset=253
	.asciz	"product"               ## string offset=275
	.asciz	"full_product"          ## string offset=283
	.asciz	"uint32_t"              ## string offset=296
	.asciz	"unsigned int"          ## string offset=305
	.asciz	"division_result"       ## string offset=318
	.asciz	"quotient"              ## string offset=334
	.asciz	"remainder"             ## string offset=343
	.asciz	"division_by_zero"      ## string offset=353
	.asciz	"augend"                ## string offset=370
	.asciz	"addend"                ## string offset=377
	.asciz	"addition"              ## string offset=384
	.asciz	"menuend"               ## string offset=393
	.asciz	"subtrahend"            ## string offset=401
	.asciz	"multiplicand"          ## string offset=412
	.asciz	"multiplier"            ## string offset=425
	.asciz	"multiplication"        ## string offset=436
	.asciz	"dividend"              ## string offset=451
	.asciz	"divisor"               ## string offset=460
	.asciz	"division"              ## string offset=468
	.section	__DWARF,__debug_loc,regular,debug
Lsection_debug_loc:
Ldebug_loc0:
.set Lset0, Lfunc_begin0-Lfunc_begin0
	.quad	Lset0
.set Lset1, Ltmp1-Lfunc_begin0
	.quad	Lset1
	.short	1                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc1:
.set Lset2, Ltmp1-Lfunc_begin0
	.quad	Lset2
.set Lset3, Ltmp2-Lfunc_begin0
	.quad	Lset3
	.short	6                       ## Loc expr size
	.byte	147                     ## DW_OP_piece
	.byte	2                       ## 2
	.byte	48                      ## DW_OP_lit0
	.byte	159                     ## DW_OP_stack_value
	.byte	147                     ## DW_OP_piece
	.byte	1                       ## 1
.set Lset4, Ltmp2-Lfunc_begin0
	.quad	Lset4
.set Lset5, Lfunc_end0-Lfunc_begin0
	.quad	Lset5
	.short	7                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	2                       ## 2
	.byte	48                      ## DW_OP_lit0
	.byte	159                     ## DW_OP_stack_value
	.byte	147                     ## DW_OP_piece
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc2:
.set Lset6, Lfunc_begin1-Lfunc_begin0
	.quad	Lset6
.set Lset7, Ltmp5-Lfunc_begin0
	.quad	Lset7
	.short	1                       ## Loc expr size
	.byte	84                      ## super-register DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc3:
.set Lset8, Ltmp6-Lfunc_begin0
	.quad	Lset8
.set Lset9, Ltmp7-Lfunc_begin0
	.quad	Lset9
	.short	1                       ## Loc expr size
	.byte	84                      ## super-register DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc4:
.set Lset10, Lfunc_begin2-Lfunc_begin0
	.quad	Lset10
.set Lset11, Ltmp9-Lfunc_begin0
	.quad	Lset11
	.short	1                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc5:
.set Lset12, Lfunc_begin3-Lfunc_begin0
	.quad	Lset12
.set Lset13, Ltmp13-Lfunc_begin0
	.quad	Lset13
	.short	1                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
.set Lset14, Ltmp13-Lfunc_begin0
	.quad	Lset14
.set Lset15, Ltmp14-Lfunc_begin0
	.quad	Lset15
	.short	1                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
.set Lset16, Ltmp14-Lfunc_begin0
	.quad	Lset16
.set Lset17, Lfunc_end3-Lfunc_begin0
	.quad	Lset17
	.short	1                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc6:
.set Lset18, Lfunc_begin3-Lfunc_begin0
	.quad	Lset18
.set Lset19, Ltmp11-Lfunc_begin0
	.quad	Lset19
	.short	1                       ## Loc expr size
	.byte	84                      ## super-register DW_OP_reg4
.set Lset20, Ltmp11-Lfunc_begin0
	.quad	Lset20
.set Lset21, Lfunc_end3-Lfunc_begin0
	.quad	Lset21
	.short	1                       ## Loc expr size
	.byte	84                      ## super-register DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc7:
.set Lset22, Ltmp15-Lfunc_begin0
	.quad	Lset22
.set Lset23, Lfunc_end3-Lfunc_begin0
	.quad	Lset23
	.short	6                       ## Loc expr size
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.byte	48                      ## DW_OP_lit0
	.byte	159                     ## DW_OP_stack_value
	.byte	147                     ## DW_OP_piece
	.byte	1                       ## 1
	.quad	0
	.quad	0
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                       ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	1                       ## DW_CHILDREN_yes
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	23                      ## DW_FORM_sec_offset
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	25                      ## DW_FORM_flag_present
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	2                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	3                       ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	4                       ## Abbreviation Code
	.byte	22                      ## DW_TAG_typedef
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	5                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	64                      ## DW_AT_frame_base
	.byte	24                      ## DW_FORM_exprloc
	.byte	122                     ## DW_AT_call_all_calls
	.byte	25                      ## DW_FORM_flag_present
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	25                      ## DW_FORM_flag_present
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	6                       ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	23                      ## DW_FORM_sec_offset
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	7                       ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	8                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	23                      ## DW_FORM_sec_offset
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	9                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	10                      ## Abbreviation Code
	.byte	72                      ## DW_TAG_call_site
	.byte	0                       ## DW_CHILDREN_no
	.byte	127                     ## DW_AT_call_origin
	.byte	19                      ## DW_FORM_ref4
	.ascii	"\202\001"              ## DW_AT_call_tail_call
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	11                      ## Abbreviation Code
	.byte	19                      ## DW_TAG_structure_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	12                      ## Abbreviation Code
	.byte	13                      ## DW_TAG_member
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	56                      ## DW_AT_data_member_location
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	0                       ## EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
	.long	546                     ## Length of Unit
	.short	4                       ## DWARF version number
.set Lset24, Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset24
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0x21b DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	46                      ## DW_AT_name
.set Lset25, Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset25
	.long	52                      ## DW_AT_comp_dir
                                        ## DW_AT_APPLE_optimized
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset26, Lfunc_end3-Lfunc_begin0    ## DW_AT_high_pc
	.long	Lset26
	.byte	2                       ## Abbrev [2] 0x2a:0x15 DW_TAG_variable
	.long	140                     ## DW_AT_name
	.long	63                      ## DW_AT_type
                                        ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_is_signed
	.byte	3                       ## Abbrev [3] 0x3f:0x7 DW_TAG_base_type
	.long	150                     ## DW_AT_name
	.byte	2                       ## DW_AT_encoding
	.byte	1                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x46:0xb DW_TAG_typedef
	.long	81                      ## DW_AT_type
	.long	156                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x51:0x7 DW_TAG_base_type
	.long	165                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	2                       ## DW_AT_byte_size
	.byte	5                       ## Abbrev [5] 0x58:0x45 DW_TAG_subprogram
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset27, Lfunc_end0-Lfunc_begin0    ## DW_AT_high_pc
	.long	Lset27
	.byte	1                       ## DW_AT_frame_base
	.byte	86
                                        ## DW_AT_call_all_calls
	.long	180                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	21                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	387                     ## DW_AT_type
                                        ## DW_AT_external
                                        ## DW_AT_APPLE_optimized
	.byte	6                       ## Abbrev [6] 0x71:0xf DW_TAG_formal_parameter
.set Lset28, Ldebug_loc0-Lsection_debug_loc ## DW_AT_location
	.long	Lset28
	.long	370                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	21                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	7                       ## Abbrev [7] 0x80:0xd DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	84
	.long	377                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	21                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	8                       ## Abbrev [8] 0x8d:0xf DW_TAG_variable
.set Lset29, Ldebug_loc1-Lsection_debug_loc ## DW_AT_location
	.long	Lset29
	.long	384                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.long	387                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	5                       ## Abbrev [5] 0x9d:0x57 DW_TAG_subprogram
	.quad	Lfunc_begin1            ## DW_AT_low_pc
.set Lset30, Lfunc_end1-Lfunc_begin1    ## DW_AT_high_pc
	.long	Lset30
	.byte	1                       ## DW_AT_frame_base
	.byte	86
                                        ## DW_AT_call_all_calls
	.long	184                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	387                     ## DW_AT_type
                                        ## DW_AT_external
                                        ## DW_AT_APPLE_optimized
	.byte	7                       ## Abbrev [7] 0xb6:0xd DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	85
	.long	393                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	6                       ## Abbrev [6] 0xc3:0xf DW_TAG_formal_parameter
.set Lset31, Ldebug_loc2-Lsection_debug_loc ## DW_AT_location
	.long	Lset31
	.long	401                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	9                       ## Abbrev [9] 0xd2:0xd DW_TAG_variable
	.byte	1                       ## DW_AT_location
	.byte	85
	.long	370                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	32                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	8                       ## Abbrev [8] 0xdf:0xf DW_TAG_variable
.set Lset32, Ldebug_loc3-Lsection_debug_loc ## DW_AT_location
	.long	Lset32
	.long	377                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	10                      ## Abbrev [10] 0xee:0x5 DW_TAG_call_site
	.long	88                      ## DW_AT_call_origin
                                        ## DW_AT_call_tail_call
	.byte	0                       ## End Of Children Mark
	.byte	5                       ## Abbrev [5] 0xf4:0x48 DW_TAG_subprogram
	.quad	Lfunc_begin2            ## DW_AT_low_pc
.set Lset33, Lfunc_end2-Lfunc_begin2    ## DW_AT_high_pc
	.long	Lset33
	.byte	1                       ## DW_AT_frame_base
	.byte	86
                                        ## DW_AT_call_all_calls
	.long	193                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	41                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	427                     ## DW_AT_type
                                        ## DW_AT_external
                                        ## DW_AT_APPLE_optimized
	.byte	6                       ## Abbrev [6] 0x10d:0xf DW_TAG_formal_parameter
.set Lset34, Ldebug_loc4-Lsection_debug_loc ## DW_AT_location
	.long	Lset34
	.long	412                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	41                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	7                       ## Abbrev [7] 0x11c:0xd DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	84
	.long	425                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	41                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	9                       ## Abbrev [9] 0x129:0x12 DW_TAG_variable
	.byte	6                       ## DW_AT_location
	.byte	147
	.byte	8
	.byte	48
	.byte	159
	.byte	147
	.byte	1
	.long	436                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	42                      ## DW_AT_decl_line
	.long	427                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	5                       ## Abbrev [5] 0x13c:0x47 DW_TAG_subprogram
	.quad	Lfunc_begin3            ## DW_AT_low_pc
.set Lset35, Lfunc_end3-Lfunc_begin3    ## DW_AT_high_pc
	.long	Lset35
	.byte	1                       ## DW_AT_frame_base
	.byte	86
                                        ## DW_AT_call_all_calls
	.long	202                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	497                     ## DW_AT_type
                                        ## DW_AT_external
                                        ## DW_AT_APPLE_optimized
	.byte	6                       ## Abbrev [6] 0x155:0xf DW_TAG_formal_parameter
.set Lset36, Ldebug_loc5-Lsection_debug_loc ## DW_AT_location
	.long	Lset36
	.long	451                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	6                       ## Abbrev [6] 0x164:0xf DW_TAG_formal_parameter
.set Lset37, Ldebug_loc6-Lsection_debug_loc ## DW_AT_location
	.long	Lset37
	.long	460                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	70                      ## DW_AT_type
	.byte	8                       ## Abbrev [8] 0x173:0xf DW_TAG_variable
.set Lset38, Ldebug_loc7-Lsection_debug_loc ## DW_AT_location
	.long	Lset38
	.long	468                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	54                      ## DW_AT_decl_line
	.long	497                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x183:0xb DW_TAG_typedef
	.long	398                     ## DW_AT_type
	.long	209                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	27                      ## DW_AT_decl_line
	.byte	11                      ## Abbrev [11] 0x18e:0x1d DW_TAG_structure_type
	.byte	4                       ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	24                      ## DW_AT_decl_line
	.byte	12                      ## Abbrev [12] 0x192:0xc DW_TAG_member
	.long	237                     ## DW_AT_name
	.long	70                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	25                      ## DW_AT_decl_line
	.byte	0                       ## DW_AT_data_member_location
	.byte	12                      ## Abbrev [12] 0x19e:0xc DW_TAG_member
	.long	244                     ## DW_AT_name
	.long	63                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	26                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x1ab:0xb DW_TAG_typedef
	.long	438                     ## DW_AT_type
	.long	253                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.byte	11                      ## Abbrev [11] 0x1b6:0x29 DW_TAG_structure_type
	.byte	12                      ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	29                      ## DW_AT_decl_line
	.byte	12                      ## Abbrev [12] 0x1ba:0xc DW_TAG_member
	.long	275                     ## DW_AT_name
	.long	70                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	0                       ## DW_AT_data_member_location
	.byte	12                      ## Abbrev [12] 0x1c6:0xc DW_TAG_member
	.long	283                     ## DW_AT_name
	.long	479                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.byte	4                       ## DW_AT_data_member_location
	.byte	12                      ## Abbrev [12] 0x1d2:0xc DW_TAG_member
	.long	244                     ## DW_AT_name
	.long	63                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	32                      ## DW_AT_decl_line
	.byte	8                       ## DW_AT_data_member_location
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x1df:0xb DW_TAG_typedef
	.long	490                     ## DW_AT_type
	.long	296                     ## DW_AT_name
	.byte	4                       ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x1ea:0x7 DW_TAG_base_type
	.long	305                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x1f1:0xb DW_TAG_typedef
	.long	508                     ## DW_AT_type
	.long	318                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	39                      ## DW_AT_decl_line
	.byte	11                      ## Abbrev [11] 0x1fc:0x29 DW_TAG_structure_type
	.byte	6                       ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	35                      ## DW_AT_decl_line
	.byte	12                      ## Abbrev [12] 0x200:0xc DW_TAG_member
	.long	334                     ## DW_AT_name
	.long	81                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	36                      ## DW_AT_decl_line
	.byte	0                       ## DW_AT_data_member_location
	.byte	12                      ## Abbrev [12] 0x20c:0xc DW_TAG_member
	.long	343                     ## DW_AT_name
	.long	81                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	37                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	12                      ## Abbrev [12] 0x218:0xc DW_TAG_member
	.long	353                     ## DW_AT_name
	.long	63                      ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	38                      ## DW_AT_decl_line
	.byte	4                       ## DW_AT_data_member_location
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.section	__DWARF,__debug_macinfo,regular,debug
Ldebug_macinfo:
	.byte	0                       ## End Of Macro List Mark
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	5                       ## Header Bucket Count
	.long	5                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	0                       ## Bucket 0
	.long	1                       ## Bucket 1
	.long	2                       ## Bucket 2
	.long	3                       ## Bucket 3
	.long	-1                      ## Bucket 4
	.long	193486030               ## Hash in Bucket 0
	.long	-1196391315             ## Hash in Bucket 1
	.long	1182035717              ## Hash in Bucket 2
	.long	2138946138              ## Hash in Bucket 3
	.long	-120491718              ## Hash in Bucket 3
.set Lset39, LNames4-Lnames_begin       ## Offset in Bucket 0
	.long	Lset39
.set Lset40, LNames3-Lnames_begin       ## Offset in Bucket 1
	.long	Lset40
.set Lset41, LNames0-Lnames_begin       ## Offset in Bucket 2
	.long	Lset41
.set Lset42, LNames1-Lnames_begin       ## Offset in Bucket 3
	.long	Lset42
.set Lset43, LNames2-Lnames_begin       ## Offset in Bucket 3
	.long	Lset43
LNames4:
	.long	180                     ## add
	.long	1                       ## Num DIEs
	.long	88
	.long	0
LNames3:
	.long	184                     ## subtract
	.long	1                       ## Num DIEs
	.long	157
	.long	0
LNames0:
	.long	193                     ## multiply
	.long	1                       ## Num DIEs
	.long	244
	.long	0
LNames1:
	.long	140                     ## is_signed
	.long	1                       ## Num DIEs
	.long	42
	.long	0
LNames2:
	.long	202                     ## divide
	.long	1                       ## Num DIEs
	.long	316
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	8                       ## Header Bucket Count
	.long	8                       ## Header Hash Count
	.long	20                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	3                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.short	3                       ## DW_ATOM_die_tag
	.short	5                       ## DW_FORM_data2
	.short	4                       ## DW_ATOM_type_flags
	.short	11                      ## DW_FORM_data1
	.long	0                       ## Bucket 0
	.long	2                       ## Bucket 1
	.long	3                       ## Bucket 2
	.long	-1                      ## Bucket 3
	.long	4                       ## Bucket 4
	.long	5                       ## Bucket 5
	.long	-1                      ## Bucket 6
	.long	7                       ## Bucket 7
	.long	249311216               ## Hash in Bucket 0
	.long	-1855312952             ## Hash in Bucket 0
	.long	1827201457              ## Hash in Bucket 1
	.long	878862258               ## Hash in Bucket 2
	.long	1457695548              ## Hash in Bucket 4
	.long	290711645               ## Hash in Bucket 5
	.long	-1304652851             ## Hash in Bucket 5
	.long	290644127               ## Hash in Bucket 7
.set Lset44, Ltypes5-Ltypes_begin       ## Offset in Bucket 0
	.long	Lset44
.set Lset45, Ltypes0-Ltypes_begin       ## Offset in Bucket 0
	.long	Lset45
.set Lset46, Ltypes6-Ltypes_begin       ## Offset in Bucket 1
	.long	Lset46
.set Lset47, Ltypes7-Ltypes_begin       ## Offset in Bucket 2
	.long	Lset47
.set Lset48, Ltypes1-Ltypes_begin       ## Offset in Bucket 4
	.long	Lset48
.set Lset49, Ltypes2-Ltypes_begin       ## Offset in Bucket 5
	.long	Lset49
.set Lset50, Ltypes3-Ltypes_begin       ## Offset in Bucket 5
	.long	Lset50
.set Lset51, Ltypes4-Ltypes_begin       ## Offset in Bucket 7
	.long	Lset51
Ltypes5:
	.long	150                     ## _Bool
	.long	1                       ## Num DIEs
	.long	63
	.short	36
	.byte	0
	.long	0
Ltypes0:
	.long	318                     ## division_result
	.long	1                       ## Num DIEs
	.long	497
	.short	22
	.byte	0
	.long	0
Ltypes6:
	.long	253                     ## multiplication_result
	.long	1                       ## Num DIEs
	.long	427
	.short	22
	.byte	0
	.long	0
Ltypes7:
	.long	165                     ## unsigned short
	.long	1                       ## Num DIEs
	.long	81
	.short	36
	.byte	0
	.long	0
Ltypes1:
	.long	209                     ## addition_subtraction_result
	.long	1                       ## Num DIEs
	.long	387
	.short	22
	.byte	0
	.long	0
Ltypes2:
	.long	296                     ## uint32_t
	.long	1                       ## Num DIEs
	.long	479
	.short	22
	.byte	0
	.long	0
Ltypes3:
	.long	305                     ## unsigned int
	.long	1                       ## Num DIEs
	.long	490
	.short	36
	.byte	0
	.long	0
Ltypes4:
	.long	156                     ## uint16_t
	.long	1                       ## Num DIEs
	.long	70
	.short	22
	.byte	0
	.long	0

.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
