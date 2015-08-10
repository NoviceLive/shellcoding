    #
    # Null-Free Exit Shellcode (Linux x86)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 18 February 2015
    #
    # GPL
    #


    .global _start
_start:
    # movl $1, %eax
    xorl %eax, %eax
    movb $1, %al

    xorl %ebx, %ebx

    int $0x80
