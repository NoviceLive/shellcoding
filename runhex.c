/*
 * Executing C-Style-Hex-Escaped String Data On The Stack
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
str2bytes (const char *str, char *bytes);

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
  str2bytes(argv[1], shellcode);

  printf("        strlen(shellcode) = %d\n", strlen(shellcode));
  printf("[+] %s\n", "executing data on the stack...");
  ((void (*)(void))shellcode)();

  return 0;
}

char *
str2bytes (const char *str, char *bytes)
{
  int n = 0;
  char buf[3];

  for(int i = 0; i < strlen(str); ++i) {
    if(str[i] == '\\') {
      strncpy(buf, str + i + 2, 2);
      buf[2] = '\0';

      bytes[n] = strtol(buf, NULL, 16);
      ++n;
    }
  }

  bytes[n] = '\0';

  return bytes;
}
