/*
 * Executing C-Style-Hex-Escaped String Data On The Stack
 *
 * Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
 *
 * GPL
 */


# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>

# ifdef __linux__
#  include <sys/mman.h>
# define SIZE_T_FMT "%zu"
# endif /* __linux__ */

# ifdef _WIN32
#  include <windows.h>
# define SIZE_T_FMT "%Iu"
# endif /* _WIN32 */


# define SIZE 4096


static char *
chexstr_to_bytes(const char *str, char *bytes);


int
main (int argc, char *argv[])
{
  char shellcode[SIZE];

  if (argc != 2) {
    printf ("%s\n", "exiting...");
    return EXIT_FAILURE;
  }

# ifdef __linux__
  int failure = mprotect ((void *)((uintptr_t)shellcode & ~4095),
                          4096,
                          PROT_READ | PROT_WRITE | PROT_EXEC);
  if (failure) {
    printf("mprotect\n");
    return EXIT_FAILURE;
  }
# endif /* __linux__ */

# ifdef _WIN32
  DWORD why_must_this_variable;
  BOOL success = VirtualProtect (shellcode, SIZE,
                                 PAGE_EXECUTE_READWRITE,
                                 &why_must_this_variable);
  if (!success) {
    printf ("VirtualProtect\n");
    return EXIT_FAILURE;
  }
# endif /* _WIN32 */

  printf("[+] %s\n", "Starting...");
  /* printf("        strlen(argv[1]) / 4 = " SIZE_T_FMT "\n", strlen(argv[1]) / 4); */
  printf("[+] %s\n", "Converting To Bytes...");
  (void)chexstr_to_bytes(argv[1], shellcode);
  printf("[+] %s\n", "Executing Data On The Stack...");
  ((void (*)(void))shellcode)();

  return EXIT_SUCCESS;
}


char *
chexstr_to_bytes(const char *chexstr, char *bytes)
{
  size_t i;
  char buf[3];
  int n = 0;
  for (i = 0; i < strlen(chexstr); ++i) {
    if (chexstr[i] == '\\') {
      strncpy(buf, chexstr + i + 2, 2);
      buf[2] = '\0';
      bytes[n] = (char)strtol(buf, NULL, 16);
      ++n;
    }
  }
  bytes[n] = '\0';
  return bytes;
}
