/*
 * Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>
 */


# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "libhex.h"

int
main(int argc, char **argv)
{
  size_t length;
  size_t i;
  if (argc != 2) {
    printf("%s\n", "Invalid Argument!");
    return EXIT_FAILURE;
  }
  length = strlen(argv[1]);

  (void)unhex(argv[1]);

  for (i = 0; i < length / 2; ++i)
    (void)putchar(argv[1][i]);

  return EXIT_SUCCESS;
}
