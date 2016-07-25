	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbx
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbx, -16
	callq	_read_int
	movl	%eax, %ebx
	callq	_read_int
	movl	%ebx, %edi
	movl	%eax, %esi
	callq	_gcd
	movl	%eax, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rbx
	retq
	.cfi_endproc

	.globl	_gcd
	.align	4, 0x90
_gcd:                                   ## @gcd
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp2:
	.cfi_def_cfa_offset 16
	movl	%edi, 4(%rsp)
	movl	%esi, (%rsp)
	testl	%esi, %esi
	je	LBB1_1
## BB#2:                                ## %Else
	movl	(%rsp), %edi
	movl	4(%rsp), %eax
	cltd
	idivl	%edi
	movl	%edx, %esi
	callq	_gcd
	popq	%rcx
	retq
LBB1_1:                                 ## %Then
	movl	4(%rsp), %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
