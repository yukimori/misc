	.file	"test_optimization.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
.L2:
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
