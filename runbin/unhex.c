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
