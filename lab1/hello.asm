global start

section .data
message: db 'hello, world!', 10

section .text
start:
	mov	rax, 0x2000001	; system call number stored in rax
	mov	rdi, 1		; destination for descriptor
	mov	rsi, message	; point to message in source register
	mov	rdx, 14		; how many bytes to write to dest
	syscall

