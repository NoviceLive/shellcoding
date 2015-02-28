/*
 * newbie's null-free exit shellcode
 *
 * by Novice Live, http://novicelive.org :)
 *
 */

/*
 * 08048054 <_start>:
 *  8048054:   31 c0                   xor    %eax,%eax
 *  8048056:   b0 01                   mov    $0x1,%al
 *  8048058:   31 db                   xor    %ebx,%ebx
 *  804805a:   cd 80                   int    $0x80
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *shellcode = "\x31\xc0"
        "\xb0\x01"
        "\x31\xdb"
        "\xcd\x80";

    printf("strlen(shellcode): %d\n", strlen(shellcode));

    ((void (*)(void))shellcode)();

    return 0;
}
