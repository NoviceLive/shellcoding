/*
 * Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>
 */


# include <stdlib.h>
# include <stdio.h>

# include "libhex.h"


int
main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s\n", "Invalied Argument!");
    return EXIT_FAILURE;
  }

  print_hex(argv[1]);

  return EXIT_SUCCESS;
}
