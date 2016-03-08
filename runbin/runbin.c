/*
Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>

This file is part of RunBin.

RunBin is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RunBin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RunBin.  If not, see <http://www.gnu.org/licenses/>.
*/


# ifndef CPP
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# endif

# include <argparse.h>

# ifdef __linux__
#  include <sys/mman.h> /* For mprotect. */
# define SIZE_T_FMT "%zu"
# endif /* __linux__ */
# ifdef _WIN32
#  include <windows.h> /* For VirtualProtect. */
# define SIZE_T_FMT "%Iu"
# endif /* _WIN32 */

# include "libhex.h"


# define SIZE 4096


void print_mem(void *addr, size_t count);

int make_exec(void *addr, size_t count);

void exec_addr(void *addr);

char *remove_chars(char *input, char * evil);


int
main (int argc, const char * argv[])
{
  int escape = 0;
  int quiet = 0;

  struct argparse argparse;
  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_BOOLEAN('e', "escape", &escape, "Use escape or raw hex."),
    OPT_BOOLEAN('q', "quiet", &quiet, "Don't confirm."),
    OPT_END()
  };
  static const char *const usage[] = {
    "runbin [-e] [-q] <filename>", NULL
  };
  argparse_init(&argparse, options, usage, 0);
  argc = argparse_parse(&argparse, argc, argv);
  if (!argc) {
    fprintf(stderr, "[x] %s\n", "Wrong arguments!");
    return EXIT_FAILURE;
  }

  char buffer[SIZE];
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
    remove_chars(buffer, "\\x\n");
    unhex(buffer);
    count = strlen(buffer);
    addr = buffer;
  } else {
    addr = buffer;
  }

  fprintf(stderr, "[-] Printing memory: %p %d\n", addr, count);
  print_mem(addr, count);

  if (!quiet) {
    fprintf(stderr, "Testing shellcode might be dangerous.\n");
    fprintf(stderr, "Are you sure? Enter to continue...");
    getchar();
  }

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


char *remove_chars(char *input, char * evil)
{
  size_t evil_len = strlen(evil);
  for (size_t round = 0; round < evil_len; round += 1) {
    size_t input_len = strlen(input);
    size_t good = 0;
    for (size_t current = 0; current < input_len; current += 1) {
      if (input[current] == evil[round]) {
        continue;
      } else {
        input[good] = input[current];
        good += 1;
      }
    }
    input[good] = '\0';
  }
  return input;
}
