	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_quickSort
	.align	4, 0x90
_quickSort:                             ## @quickSort
	.cfi_startproc
## BB#0:                                ## %entry
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	retq
	.cfi_endproc


.subsections_via_symbols
