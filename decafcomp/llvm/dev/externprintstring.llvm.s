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
	movl	$1, 4(%rsp)
	leaq	L_globalstring(%rip), %rdi
	callq	_print_string
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_globalstring:                         ## @globalstring
	.asciz	"hello world\n"


.subsections_via_symbols
