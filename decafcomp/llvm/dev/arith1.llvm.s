	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movb	$0, 7(%rsp)
	movb	$0, 6(%rsp)
	movb	$0, 5(%rsp)
	movb	$0, 4(%rsp)
	movl	$0, (%rsp)
	movb	$1, 6(%rsp)
	movb	$0, 5(%rsp)
	movb	$1, 4(%rsp)
	movb	6(%rsp), %cl
	notb	%cl
	movb	$1, %al
	testb	$1, %cl
	je	LBB0_4
## BB#1:                                ## %False
	movzbl	5(%rsp), %eax
	andl	$1, %eax
	cmpl	$1, %eax
	je	LBB0_3
## BB#2:
	xorl	%eax, %eax
	jmp	LBB0_4
LBB0_3:                                 ## %True6
	movb	4(%rsp), %al
	xorb	$1, %al
LBB0_4:                                 ## %BooleanShortCircuit9
	andb	$1, %al
	movb	%al, 7(%rsp)
	movl	$0, (%rsp)
	xorl	%edi, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
