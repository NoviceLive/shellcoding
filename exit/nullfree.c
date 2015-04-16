#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\x31\xc0\xb0\x01\x31\xdb\xcd\x80";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
