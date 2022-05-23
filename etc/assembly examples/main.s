.LC0:
	.string	"Hello\n"
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmp		$0, %ebx
	je .IF01
	jg .IF02
.IF01:
	mov $1, %eax
	jmp .IF03
.IF02:
	mov $0, %eax
	jmp .IF03
.IF03:
	movl	$0, %eax
	leave
	ret

