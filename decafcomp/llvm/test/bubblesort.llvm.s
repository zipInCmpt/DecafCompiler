	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %ForBegin
	pushq	%r14
Ltmp0:
	.cfi_def_cfa_offset 16
	pushq	%rbx
Ltmp1:
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
Ltmp2:
	.cfi_def_cfa_offset 48
Ltmp3:
	.cfi_offset %rbx, -24
Ltmp4:
	.cfi_offset %r14, -16
	movl	$0, 20(%rsp)
	movl	$0, 16(%rsp)
	movl	$0, 12(%rsp)
	callq	_read_int
	movl	%eax, 20(%rsp)
	movl	$0, 16(%rsp)
	leaq	_a(%rip), %rbx
	jmp	LBB0_1
	.align	4, 0x90
LBB0_2:                                 ## %ForAfter
                                        ##   in Loop: Header=BB0_1 Depth=1
	movslq	16(%rsp), %r14
	callq	_read_int
	movl	%eax, (%rbx,%r14,4)
	incl	16(%rsp)
LBB0_1:                                 ## %ForCond
                                        ## =>This Inner Loop Header: Depth=1
	movl	16(%rsp), %eax
	cmpl	20(%rsp), %eax
	jl	LBB0_2
## BB#3:                                ## %ForBegin6
	movl	$0, 16(%rsp)
	jmp	LBB0_4
	.align	4, 0x90
LBB0_10:                                ## %ForAfter59
                                        ##   in Loop: Header=BB0_4 Depth=1
	incl	16(%rsp)
LBB0_4:                                 ## %ForCond7
                                        ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_6 Depth 2
	movl	20(%rsp), %eax
	decl	%eax
	cmpl	%eax, 16(%rsp)
	jge	LBB0_11
## BB#5:                                ## %ForBegin13
                                        ##   in Loop: Header=BB0_4 Depth=1
	movl	16(%rsp), %eax
	incl	%eax
	movl	%eax, 12(%rsp)
	jmp	LBB0_6
	.align	4, 0x90
LBB0_9:                                 ## %ForAfter55
                                        ##   in Loop: Header=BB0_6 Depth=2
	incl	12(%rsp)
LBB0_6:                                 ## %ForCond16
                                        ##   Parent Loop BB0_4 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	12(%rsp), %eax
	cmpl	20(%rsp), %eax
	jge	LBB0_10
## BB#7:                                ## %ForExec21
                                        ##   in Loop: Header=BB0_6 Depth=2
	movslq	16(%rsp), %rax
	movl	(%rbx,%rax,4), %eax
	movslq	12(%rsp), %rcx
	cmpl	(%rbx,%rcx,4), %eax
	jle	LBB0_9
## BB#8:                                ## %Then
                                        ##   in Loop: Header=BB0_6 Depth=2
	movslq	16(%rsp), %rax
	movslq	12(%rsp), %rcx
	movl	(%rbx,%rcx,4), %ecx
	addl	%ecx, (%rbx,%rax,4)
	movslq	12(%rsp), %rax
	movslq	16(%rsp), %rcx
	movl	(%rbx,%rcx,4), %ecx
	subl	(%rbx,%rax,4), %ecx
	movl	%ecx, (%rbx,%rax,4)
	movslq	16(%rsp), %rax
	movslq	12(%rsp), %rcx
	movl	(%rbx,%rcx,4), %ecx
	subl	%ecx, (%rbx,%rax,4)
	jmp	LBB0_9
LBB0_11:                                ## %ForBegin63
	movl	$0, 16(%rsp)
	jmp	LBB0_12
	.align	4, 0x90
LBB0_13:                                ## %ForAfter73
                                        ##   in Loop: Header=BB0_12 Depth=1
	movslq	16(%rsp), %rax
	movl	(%rbx,%rax,4), %edi
	callq	_print_int
	incl	16(%rsp)
LBB0_12:                                ## %ForCond64
                                        ## =>This Inner Loop Header: Depth=1
	movl	16(%rsp), %eax
	cmpl	20(%rsp), %eax
	jl	LBB0_13
## BB#14:                               ## %ForEnd76
	xorl	%eax, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%r14
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,40,4

.subsections_via_symbols
