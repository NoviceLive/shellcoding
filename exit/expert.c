#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\x6a\x01\x58\x31\xdb\xcd\x80";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
