	# # # # # # # # # # # # # # # # # # # #
	# newbie-exit.s by Novice Live, http://novicelive.org :)
	#
	# feb 18, 2015
	# # # # # # # # # # # # # # # # # # # #

	.global _start
_start:
	# void _exit(int status);
	movl $1, %eax
	movl $233, %ebx # why not 23333333333....
	int $0x80
