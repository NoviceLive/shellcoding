#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\xb8\x01\x00\x00\x00\xbb\xe9\x00\x00\x00\xcd\x80";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
