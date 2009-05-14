	.text
.globl _fibo
_fibo:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$36, %esp
	cmpl	$1, 8(%ebp)
	jg	L2
	movl	$1, -12(%ebp)
	jmp	L4
L2:
	movl	8(%ebp), %eax
	decl	%eax
	movl	%eax, (%esp)
	call	_fibo
	movl	%eax, %esi
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	_fibo
	addl	%eax, %esi
	movl	%esi, -12(%ebp)
L4:
	movl	-12(%ebp), %eax
	addl	$36, %esp
	popl	%esi
	leave
	ret
	.subsections_via_symbols
