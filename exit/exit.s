	# # # # # # # # # # # # # # # # # # # #
	# exit.s by Novice Live, http://novicelive.org :)
	#
	# feb 18, 2015
	# # # # # # # # # # # # # # # # # # # #

	.global _start
_start:
	# void _exit(int status);
	xorl %eax, %eax
	movb $1, %al
	xorl %ebx, %ebx # why not 2333333333....
	int $0x80
