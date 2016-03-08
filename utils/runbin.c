/*
 * Executing C-Style-Hex-Escaped String Data On The Stack
 *
 * Copyright 2015 Gu Zhengxiong <rectigu@gmail.com>
 *
 */


# ifndef CPP
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# endif

# ifdef __linux__
#  include <sys/mman.h> /* For mprotect */
# define SIZE_T_FMT "%zu"
# endif /* __linux__ */

# ifdef _WIN32
#  include <windows.h> /* For VirtualProtect */
# define SIZE_T_FMT "%Iu"
# endif /* _WIN32 */

# include <argparse.h>


# define SIZE 4096


char *
esc_str_to_bytes(const char *str, char *bytes);

void print_mem(void *addr, size_t count);

int make_exec(void *addr, size_t count);

void exec_addr(void *addr);


int
main (int argc, const char * argv[])
{
  int escape = 0;

  struct argparse argparse;
  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_BOOLEAN('e', "escape", &escape, "Use escape mode."),
    OPT_END()
  };
  static const char *const usage[] = {
    "runbin [-e] <filename>", NULL
  };
  argparse_init(&argparse, options, usage, 0);
  argc = argparse_parse(&argparse, argc, argv);
  if (!argc) {
    fprintf(stderr, "[x] %s\n", "Wrong arguments!");
    return EXIT_FAILURE;
  }

  char buffer[SIZE];
  char shellcode[SIZE];
  const char *filename = argv[0];
  FILE *stream = fopen(filename, "rb");
  if (stream == NULL) {
    fprintf(stderr, "[x] Error opening file: %s\n", filename);
    return EXIT_FAILURE;
  }
  size_t count = fread(buffer, 1, SIZE, stream);
  if (ferror(stream)) {
    fprintf(stderr, "[x] Error reading file: %s\n", filename);
    fclose(stream);
    return EXIT_FAILURE;
  }
  fclose(stream);

  void *addr = NULL;
  if (escape) {
    (void)esc_str_to_bytes(buffer, shellcode);
    count = strlen(shellcode);
    addr = shellcode;
  } else {
    addr = buffer;
  }

  fprintf(stderr, "[-] Printing memory: %p %d\n", addr, count);
  print_mem(addr, count);
  if (make_exec(addr, count)) {
    fprintf(stderr, "[-] Executing address: %p\n", addr);
    exec_addr(addr);
  } else {
    fprintf(stderr, "[x] Error Making Exec: %p\n", addr);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


void print_mem(void *addr, size_t count)
{
  for (size_t current = 0; current < count; current += 1) {
    if (current && current % 16 == 0) {
      putchar('\n');
    }
    printf("%02x ", *((unsigned char *)addr + current));
  }
  putchar('\n');
}


int make_exec(void *addr, size_t count)
{
# ifdef __linux__
  int failure = mprotect ((void *)((uintptr_t)addr & ~4095),
                          count,
                          PROT_READ | PROT_WRITE | PROT_EXEC);
  return failure ? 0 : 1;
# endif /* __linux__ */

# ifdef _WIN32
  DWORD why_must_this_variable;
  BOOL success = VirtualProtect (addr, count,
                                 PAGE_EXECUTE_READWRITE,
                                 &why_must_this_variable);
  return success ? 1 : 0;
# endif /* _WIN32 */
}


void exec_addr(void *addr)
{
  ((void (*)(void))addr)();
}


char *
esc_str_to_bytes(const char *chexstr, char *bytes)
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
