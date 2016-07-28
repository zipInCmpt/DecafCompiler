	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_f
	.align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	jmp	LBB0_1
	.align	4, 0x90
LBB0_3:                                 ## %IfCont
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	4(%rsp), %edi
	callq	_print_int
LBB0_1:                                 ## %WhileCond
                                        ## =>This Inner Loop Header: Depth=1
	cmpl	$9, 4(%rsp)
	jg	LBB0_4
## BB#2:                                ## %While
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	4(%rsp), %eax
	incl	%eax
	movl	%eax, 4(%rsp)
	cmpl	$5, %eax
	jne	LBB0_3
LBB0_4:                                 ## %WhileEnd
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
