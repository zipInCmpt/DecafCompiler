	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_test
	.align	4, 0x90
_test:                                  ## @test
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movb	%dil, %al
	andb	$1, %al
	movb	%al, 7(%rsp)
	notb	%dil
	movb	$1, %al
	testb	$1, %dil
	je	LBB0_2
## BB#1:                                ## %False
	xorl	%eax, %eax
LBB0_2:                                 ## %BooleanShortCircuit
	movzbl	%al, %edi
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
	movl	$1, %edi
	callq	_test
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
