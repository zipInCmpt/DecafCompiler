	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %BooleanShortCircuit
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movb	$0, 3(%rsp)
	movb	$0, 2(%rsp)
	movl	$958, 4(%rsp)           ## imm = 0x3BE
	movl	$-958, 4(%rsp)          ## imm = 0xFFFFFFFFFFFFFC42
	movb	$1, 3(%rsp)
	movb	$0, 2(%rsp)
	movb	3(%rsp), %cl
	notb	%cl
	movb	$1, %al
	testb	$1, %cl
	je	LBB0_2
## BB#1:                                ## %False5
	movb	2(%rsp), %al
LBB0_2:                                 ## %BooleanShortCircuit7
	andb	$1, %al
	movb	%al, 3(%rsp)
	movl	4(%rsp), %edi
	negl	%edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
