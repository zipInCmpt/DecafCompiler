	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_fib
	.align	4, 0x90
_fib:                                   ## @fib
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbx
Ltmp0:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
Ltmp1:
	.cfi_def_cfa_offset 32
Ltmp2:
	.cfi_offset %rbx, -16
	movl	%edi, 12(%rsp)
	movb	$1, %al
	testl	%edi, %edi
	je	LBB0_2
## BB#1:                                ## %False
	cmpl	$1, 12(%rsp)
	sete	%al
LBB0_2:                                 ## %BooleanShortCircuit
	testb	%al, %al
	jne	LBB0_3
## BB#5:                                ## %IfCont
	movl	12(%rsp), %edi
	decl	%edi
	callq	_fib
	movl	%eax, %ebx
	movl	12(%rsp), %edi
	addl	$-2, %edi
	callq	_fib
	addl	%ebx, %eax
	jmp	LBB0_4
LBB0_3:                                 ## %Then
	movl	12(%rsp), %eax
LBB0_4:                                 ## %Then
	addq	$16, %rsp
	popq	%rbx
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp3:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	callq	_read_int
	movl	%eax, 4(%rsp)
	movl	%eax, %edi
	callq	_fib
	movl	%eax, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
