	.text
	.file	"program.c"
	.globl	main                            # -- Begin function main
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	movl	$18620, %eax                    # imm = 0x48BC
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 20.0.0 (++20240825053637+0916ae49b89d-1~exp1~20240825053808.1886)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
