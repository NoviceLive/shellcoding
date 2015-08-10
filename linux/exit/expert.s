    #
    # Expert's Null-Free Exit Shellcode (Linux x86)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 16 April 2015
    #
    # GPL
    #


    .global _start
_start:
    # xorl %eax, %eax
    # movb $1, %al
    pushl $1
    popl %eax

    xorl %ebx, %ebx

    int $0x80
