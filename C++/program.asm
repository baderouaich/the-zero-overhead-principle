	.file	"program.cpp"
	.text
	.section	.text._ZN6Player9move_leftEi,"axG",@progbits,_ZN6Player9move_leftEi,comdat
	.align 2
	.weak	_ZN6Player9move_leftEi
	.type	_ZN6Player9move_leftEi, @function
_ZN6Player9move_leftEi:
.LFB12:
	.cfi_startproc
	endbr64
	subl	%esi, 8(%rdi)
	ret
	.cfi_endproc
.LFE12:
	.size	_ZN6Player9move_leftEi, .-_ZN6Player9move_leftEi
	.section	.text._ZN6Player10move_rightEi,"axG",@progbits,_ZN6Player10move_rightEi,comdat
	.align 2
	.weak	_ZN6Player10move_rightEi
	.type	_ZN6Player10move_rightEi, @function
_ZN6Player10move_rightEi:
.LFB13:
	.cfi_startproc
	endbr64
	addl	%esi, 8(%rdi)
	ret
	.cfi_endproc
.LFE13:
	.size	_ZN6Player10move_rightEi, .-_ZN6Player10move_rightEi
	.section	.text._ZN6Player7move_upEi,"axG",@progbits,_ZN6Player7move_upEi,comdat
	.align 2
	.weak	_ZN6Player7move_upEi
	.type	_ZN6Player7move_upEi, @function
_ZN6Player7move_upEi:
.LFB14:
	.cfi_startproc
	endbr64
	subl	%esi, 12(%rdi)
	ret
	.cfi_endproc
.LFE14:
	.size	_ZN6Player7move_upEi, .-_ZN6Player7move_upEi
	.section	.text._ZN6Player9move_downEi,"axG",@progbits,_ZN6Player9move_downEi,comdat
	.align 2
	.weak	_ZN6Player9move_downEi
	.type	_ZN6Player9move_downEi, @function
_ZN6Player9move_downEi:
.LFB15:
	.cfi_startproc
	endbr64
	addl	%esi, 12(%rdi)
	ret
	.cfi_endproc
.LFE15:
	.size	_ZN6Player9move_downEi, .-_ZN6Player9move_downEi
	.section	.text._ZN6PlayerpLEi,"axG",@progbits,_ZN6PlayerpLEi,comdat
	.align 2
	.weak	_ZN6PlayerpLEi
	.type	_ZN6PlayerpLEi, @function
_ZN6PlayerpLEi:
.LFB16:
	.cfi_startproc
	endbr64
	addl	%esi, 8(%rdi)
	movq	%rdi, %rax
	addl	%esi, 12(%rdi)
	ret
	.cfi_endproc
.LFE16:
	.size	_ZN6PlayerpLEi, .-_ZN6PlayerpLEi
	.section	.text._ZN6PlayerD2Ev,"axG",@progbits,_ZN6PlayerD5Ev,comdat
	.align 2
	.weak	_ZN6PlayerD2Ev
	.type	_ZN6PlayerD2Ev, @function
_ZN6PlayerD2Ev:
.LFB19:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE19:
	.size	_ZN6PlayerD2Ev, .-_ZN6PlayerD2Ev
	.weak	_ZN6PlayerD1Ev
	.set	_ZN6PlayerD1Ev,_ZN6PlayerD2Ev
	.section	.text._ZN6PlayerD0Ev,"axG",@progbits,_ZN6PlayerD5Ev,comdat
	.align 2
	.weak	_ZN6PlayerD0Ev
	.type	_ZN6PlayerD0Ev, @function
_ZN6PlayerD0Ev:
.LFB21:
	.cfi_startproc
	endbr64
	movl	$16, %esi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE21:
	.size	_ZN6PlayerD0Ev, .-_ZN6PlayerD0Ev
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB17:
	.cfi_startproc
	endbr64
	movl	$27872, %eax
	ret
	.cfi_endproc
.LFE17:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 14.2.0-4ubuntu2~24.04) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
