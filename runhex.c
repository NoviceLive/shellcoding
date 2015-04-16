/*
 * Executing Hex String Data On The Stack
 *
 * 16 April 2015
 *
 * Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
 *
 * GPL
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *
hexstr2shellcode(const char *hexstr, char *shellcode);

int
main (int argc, char *argv[])
{
  if(argc != 2) {
    printf("%s\n", "exiting...");
    exit(-1);
  }

  char shellcode[1024];

  printf("[+] %s\n", "starting...");
  printf("        strlen(argv[1]) = %d\n", strlen(argv[1]));

  printf("[+] %s\n", "converting to shellcode...");
  hexstr2shellcode(argv[1], shellcode);

  printf("        strlen(shellcode) = %d\n", strlen(shellcode));
  printf("[+] %s\n", "executing data on the stack...");
  ((void (*)(void))shellcode)();

  return 0;
}

char *
hexstr2shellcode(const char *hexstr, char *shellcode)
{
  int n = 0;
  char buf[3];

  for(int i = 0; i < strlen(hexstr); ++i) {
    if(hexstr[i] == '\\') {
      strncpy(buf, hexstr + i + 2, 2);
      buf[2] = '\0';

      shellcode[n] = strtol(buf, NULL, 16);
      ++n;
    }
  }

  shellcode[n] = '\0';

  return shellcode;
}
