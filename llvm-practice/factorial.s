	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_factorial
	.align	4, 0x90
_factorial:                             ## @factorial
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbx
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbx, -16
	movl	%edi, %ebx
	testl	%ebx, %ebx
	je	LBB0_2
## BB#1:                                ## %recurse
	leal	-1(%rbx), %edi
	callq	_factorial
	imull	%ebx, %eax
	popq	%rbx
	retq
LBB0_2:                                 ## %done
	movl	$1, %eax
	popq	%rbx
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp2:
	.cfi_def_cfa_offset 16
	movl	$11, %edi
	callq	_factorial
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
