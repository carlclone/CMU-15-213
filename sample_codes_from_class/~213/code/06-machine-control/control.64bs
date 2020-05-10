	.file	"control.c"
	.text
	.globl	gt
	.type	gt, @function
gt:
.LFB18:
	.cfi_startproc
	cmpq	%rsi, %rdi
	setg	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE18:
	.size	gt, .-gt
	.globl	zero
	.type	zero, @function
zero:
.LFB19:
	.cfi_startproc
	testq	%rdi, %rdi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE19:
	.size	zero, .-zero
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB20:
	.cfi_startproc
	cmpq	%rsi, %rdi
	jle	.L4
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
.L4:
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
	.cfi_endproc
.LFE20:
	.size	absdiff, .-absdiff
	.globl	absdiff_j
	.type	absdiff_j, @function
absdiff_j:
.LFB21:
	.cfi_startproc
	cmpq	%rsi, %rdi
	jle	.L7
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
.L7:
	movq	%rsi, %rax
	subq	%rdi, %rax
.L8:
	ret
	.cfi_endproc
.LFE21:
	.size	absdiff_j, .-absdiff_j
	.globl	absdiff_cm
	.type	absdiff_cm, @function
absdiff_cm:
.LFB22:
	.cfi_startproc
	movq	%rdi, %rax
	subq	%rsi, %rax
	movq	%rsi, %rdx
	subq	%rdi, %rdx
	cmpq	%rsi, %rdi
	jg	.L10
	movq	%rdx, %rax
.L10:
	rep; ret
	.cfi_endproc
.LFE22:
	.size	absdiff_cm, .-absdiff_cm
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"x = %d, y = %d, absdiff --> %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsi, %rbp
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movq	%rax, %rbx
	movq	16(%rbp), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movq	%rax, %rbp
	movslq	%eax, %rsi
	movslq	%ebx, %rdi
	call	absdiff
	movl	%eax, %ecx
	movl	%ebp, %edx
	movl	%ebx, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
