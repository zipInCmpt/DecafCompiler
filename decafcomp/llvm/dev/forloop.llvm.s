	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_f
	.align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## BB#0:                                ## %ForBegin
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	jmp	LBB0_1
	.align	4, 0x90
LBB0_5:                                 ## %ForAfter
                                        ##   in Loop: Header=BB0_1 Depth=1
	incl	4(%rsp)
LBB0_1:                                 ## %ForCond
                                        ## =>This Inner Loop Header: Depth=1
	cmpl	$9, 4(%rsp)
	jg	LBB0_6
## BB#2:                                ## %ForExec
                                        ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$5, 4(%rsp)
	je	LBB0_5
## BB#3:                                ## %IfCont
                                        ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$8, 4(%rsp)
	je	LBB0_6
## BB#4:                                ## %IfCont9
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	4(%rsp), %edi
	callq	_print_int
	jmp	LBB0_5
LBB0_6:                                 ## %ForEnd
	movl	4(%rsp), %edi
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	callq	_f
	popq	%rax
	retq
	.cfi_endproc


.subsections_via_symbols
