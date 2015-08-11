/*
 * Executing C-Style-Hex-Escaped String Data On The Stack
 *
 * Copyright (C) 2015 Gu Zhengxiong (rectigu@gmail.com)
 *
 * GPL
 */



# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>

# ifdef __linux__
# include <sys/mman.h>
# endif /* __linux__ */

# ifdef _WIN32
# include <windows.h>
# endif /* _WIN32 */


# define SIZE 4096


char *
str2bytes(const char *str, char *bytes);


int
main (int argc, char *argv[])
{
  if (argc != 2) {
    printf ("%s\n", "exiting...");
    exit (-1);
  }

  char shellcode[SIZE];

# ifdef __linux__
  int ret = mprotect ((void *)((uintptr_t)shellcode & ~4095), 4096,
                      PROT_READ | PROT_WRITE | PROT_EXEC);

  if (ret) {
    printf("mprotect\n");
    return EXIT_FAILURE;
  }
# endif /* __linux__ */

# ifdef _WIN32
  DWORD why_must_this_variable;
  BOOL ret = VirtualProtect (shellcode, strlen(shellcode),
                  PAGE_EXECUTE_READWRITE, &why_must_this_variable);
  if (!ret) {
    printf ("VirtualProtect\n");
    return EXIT_FAILURE;
  }
# endif /* _WIN32 */

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
str2bytes(const char *str, char *bytes)
{
  int n = 0;
  char buf[3];

  for (int i = 0; i < strlen(str); ++i) {
    if (str[i] == '\\') {
      strncpy(buf, str + i + 2, 2);
      buf[2] = '\0';

      bytes[n] = strtol(buf, NULL, 16);
      ++n;
    }
  }

  bytes[n] = '\0';

  return bytes;
}
