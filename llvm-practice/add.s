	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_add1
	.align	4, 0x90
_add1:                                  ## @add1
	.cfi_startproc
## BB#0:                                ## %entry
	leal	(%rdi,%rsi), %eax
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
	movl	$3, %edi
	movl	$4, %esi
	callq	_add1
	movl	%eax, %edi
	callq	_print_int
	leaq	_.nl(%rip), %rdi
	callq	_print_string
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.section	__TEXT,__const
	.globl	_.nl                    ## @.nl
_.nl:
	.asciz	"\n"


.subsections_via_symbols
