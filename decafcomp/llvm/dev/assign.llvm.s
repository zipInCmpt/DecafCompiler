	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_f
	.align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movabsq	$4294967297, %rax       ## imm = 0x100000001
	movq	%rax, _a(%rip)
	movl	_a(%rip), %edi
	callq	_print_int
	movl	_a+4(%rip), %edi
	callq	_print_int
	movl	_a+8(%rip), %edi
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	callq	_f
	popq	%rax
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,400,4

.subsections_via_symbols
