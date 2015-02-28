/*
 * newbie's exit shellcode, with null bytes
 *
 * by Novice Live, http://novicelive.org :)
 *
 * feb 18, 2015
 */

/*
 * 08048054 <_start>:
 *  8048054:   b8 01 00 00 00          mov    $0x1,%eax
 *  8048059:   bb e9 00 00 00          mov    $0xe9,%ebx
 *  804805e:   cd 80                   int    $0x80
 */

int main(void)
{
    char *shellcode = "\xb8\x01\x00\x00\x00"
        "\xbb\xe9\x00\x00\x00"
        "\xcd\x80";

    ((void (*)(void))shellcode)();

    return 0;
}
