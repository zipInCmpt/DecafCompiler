	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_partition
	.align	4, 0x90
_partition:                             ## @partition
	.cfi_startproc
## BB#0:                                ## %entry
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	movl	$0, -12(%rsp)
	leaq	_a(%rip), %rax
	movslq	-4(%rsp), %rcx
	movl	(%rax,%rcx,4), %ecx
	movl	%ecx, -12(%rsp)
	jmp	LBB0_1
	.align	4, 0x90
LBB0_15:                                ## %Then50
                                        ##   in Loop: Header=BB0_1 Depth=1
	movslq	-8(%rsp), %rcx
	movslq	-4(%rsp), %rdx
	movl	(%rax,%rdx,4), %edx
	movl	%edx, (%rax,%rcx,4)
	decl	-8(%rsp)
LBB0_1:                                 ## %WhileCond
                                        ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_2 Depth 2
	movl	-4(%rsp), %ecx
	cmpl	-8(%rsp), %ecx
	jl	LBB0_2
	jmp	LBB0_16
	.align	4, 0x90
LBB0_6:                                 ## %While14
                                        ##   in Loop: Header=BB0_2 Depth=2
	decl	-8(%rsp)
LBB0_2:                                 ## %WhileCond4
                                        ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-4(%rsp), %ecx
	cmpl	-8(%rsp), %ecx
	jl	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_2 Depth=2
	xorl	%ecx, %ecx
	jmp	LBB0_5
	.align	4, 0x90
LBB0_4:                                 ## %True
                                        ##   in Loop: Header=BB0_2 Depth=2
	movl	-12(%rsp), %ecx
	movslq	-8(%rsp), %rdx
	cmpl	(%rax,%rdx,4), %ecx
	setle	%cl
LBB0_5:                                 ## %BooleanShortCircuit
                                        ##   in Loop: Header=BB0_2 Depth=2
	testb	%cl, %cl
	jne	LBB0_6
## BB#7:                                ## %WhileEnd
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rsp), %ecx
	cmpl	-8(%rsp), %ecx
	jge	LBB0_10
## BB#8:                                ## %Then
                                        ##   in Loop: Header=BB0_1 Depth=1
	movslq	-4(%rsp), %rcx
	movslq	-8(%rsp), %rdx
	movl	(%rax,%rdx,4), %edx
	movl	%edx, (%rax,%rcx,4)
	.align	4, 0x90
LBB0_9:                                 ## %WhileCond26
                                        ##   in Loop: Header=BB0_1 Depth=1
	incl	-4(%rsp)
LBB0_10:                                ## %WhileCond26
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rsp), %ecx
	cmpl	-8(%rsp), %ecx
	jl	LBB0_12
## BB#11:                               ##   in Loop: Header=BB0_1 Depth=1
	xorl	%ecx, %ecx
	jmp	LBB0_13
	.align	4, 0x90
LBB0_12:                                ## %True32
                                        ##   in Loop: Header=BB0_1 Depth=1
	movslq	-4(%rsp), %rcx
	movl	(%rax,%rcx,4), %ecx
	cmpl	-12(%rsp), %ecx
	setle	%cl
LBB0_13:                                ## %BooleanShortCircuit39
                                        ##   in Loop: Header=BB0_1 Depth=1
	testb	%cl, %cl
	jne	LBB0_9
## BB#14:                               ## %WhileEnd45
                                        ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rsp), %ecx
	cmpl	-8(%rsp), %ecx
	jge	LBB0_1
	jmp	LBB0_15
LBB0_16:                                ## %WhileEnd60
	movslq	-4(%rsp), %rcx
	movl	-12(%rsp), %edx
	movl	%edx, (%rax,%rcx,4)
	movl	-4(%rsp), %eax
	retq
	.cfi_endproc

	.globl	_qsort
	.align	4, 0x90
_qsort:                                 ## @qsort
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$24, %rsp
Ltmp0:
	.cfi_def_cfa_offset 32
	movl	%edi, 20(%rsp)
	movl	%esi, 16(%rsp)
	movl	%edx, 12(%rsp)
	movl	$0, 8(%rsp)
	movl	20(%rsp), %eax
	cmpl	16(%rsp), %eax
	jge	LBB1_1
## BB#2:                                ## %IfCont
	movl	20(%rsp), %edi
	movl	16(%rsp), %esi
	callq	_partition
	movl	%eax, 8(%rsp)
	movl	20(%rsp), %edi
	leal	-1(%rax), %esi
	movl	12(%rsp), %edx
	callq	_qsort
	movl	8(%rsp), %edi
	incl	%edi
	movl	16(%rsp), %esi
	movl	12(%rsp), %edx
	callq	_qsort
	addq	$24, %rsp
	retq
LBB1_1:                                 ## %Then
	addq	$24, %rsp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%r14
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
	.cfi_offset %r14, -16
	movl	$0, 4(%rsp)
	movl	$0, (%rsp)
	callq	_read_int
	movl	%eax, 4(%rsp)
	movl	$0, (%rsp)
	leaq	_a(%rip), %r14
	jmp	LBB2_1
	.align	4, 0x90
LBB2_2:                                 ## %ForExec
                                        ##   in Loop: Header=BB2_1 Depth=1
	movslq	(%rsp), %rbx
	callq	_read_int
	movl	%eax, (%r14,%rbx,4)
	incl	(%rsp)
LBB2_1:                                 ## %ForCond
                                        ## =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	cmpl	4(%rsp), %eax
	jl	LBB2_2
## BB#3:                                ## %ForEnd
	movl	4(%rsp), %edx
	leal	-1(%rdx), %esi
	xorl	%edi, %edi
	callq	_qsort
	movl	$0, (%rsp)
	jmp	LBB2_4
	.align	4, 0x90
LBB2_5:                                 ## %ForExec14
                                        ##   in Loop: Header=BB2_4 Depth=1
	movslq	(%rsp), %rax
	movl	(%r14,%rax,4), %edi
	callq	_print_int
	incl	(%rsp)
LBB2_4:                                 ## %ForCond9
                                        ## =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	cmpl	4(%rsp), %eax
	jl	LBB2_5
## BB#6:                                ## %ForEnd20
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,40,4

.subsections_via_symbols
