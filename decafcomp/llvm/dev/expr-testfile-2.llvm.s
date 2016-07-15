	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$958, 4(%rsp)           ## imm = 0x3BE
	movl	$-958, 4(%rsp)          ## imm = 0xFFFFFFFFFFFFFC42
	movb	$1, 3(%rsp)
	movb	$0, 2(%rsp)
	movl	4(%rsp), %edi
	negl	%edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
