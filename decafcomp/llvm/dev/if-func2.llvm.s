	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_f
	.align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## BB#0:                                ## %entry
	movb	$1, %al
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	callq	_f
	testb	$1, %al
	jne	LBB1_1
## BB#2:                                ## %Else
	movl	$2, 4(%rsp)
	jmp	LBB1_3
LBB1_1:                                 ## %Then
	movl	$1, 4(%rsp)
LBB1_3:                                 ## %IfCont
	movl	4(%rsp), %edi
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc


.subsections_via_symbols
