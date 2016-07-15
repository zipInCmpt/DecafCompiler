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
	callq	_read_int
	movl	%eax, %edi
	callq	_cat
	movl	%eax, %edi
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc

	.globl	_fact
	.align	4, 0x90
_fact:                                  ## @fact
	.cfi_startproc
## BB#0:                                ## %entry
	movl	%edi, -4(%rsp)
	xorl	%eax, %eax
	retq
	.cfi_endproc

	.globl	_choose
	.align	4, 0x90
_choose:                                ## @choose
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbp
Ltmp1:
	.cfi_def_cfa_offset 16
	pushq	%rbx
Ltmp2:
	.cfi_def_cfa_offset 24
	pushq	%rax
Ltmp3:
	.cfi_def_cfa_offset 32
Ltmp4:
	.cfi_offset %rbx, -24
Ltmp5:
	.cfi_offset %rbp, -16
	movl	%edi, 4(%rsp)
	movl	%esi, (%rsp)
	movl	4(%rsp), %edi
	callq	_fact
	movl	%eax, %ebx
	movl	(%rsp), %edi
	callq	_fact
	movl	%eax, %ebp
	movl	4(%rsp), %edi
	subl	(%rsp), %edi
	callq	_fact
	movl	%eax, %ecx
	imull	%ebp, %ecx
	movl	%ebx, %eax
	cltd
	idivl	%ecx
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_cat
	.align	4, 0x90
_cat:                                   ## @cat
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp6:
	.cfi_def_cfa_offset 16
	movl	%edi, %eax
	movl	%eax, 4(%rsp)
	leal	(%rax,%rax), %edi
	movl	%eax, %esi
	callq	_choose
	movl	4(%rsp), %ecx
	incl	%ecx
	cltd
	idivl	%ecx
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
