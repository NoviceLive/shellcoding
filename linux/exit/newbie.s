    #
    # Newbie's Exit Shellcode With Null Bytes (Linux x86)
    #
    # Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
    #
    # 18 February 2015
    #
    # GPL
    #


    .global _start
_start:
    # __NR_exit 1
    movl $1, %eax

    # int status
    movl $233, %ebx

    int $0x80
