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


void
print_hex(char *string)
{
  size_t i;
  for (i = 0; i < strlen(string); ++i)
    printf("%x", (unsigned int)string[i]);

  (void)putchar('\n');
}


char *
unhex(char *string)
{
  char temp[3];
  size_t i;
  size_t length = strlen(string);
  for (i = 0; i < length; i += 2) {
    strncpy(temp, string + i, 2);
    string[i / 2] = (char)strtoul(temp, NULL, 16);
  }
  string[i / 2] = (char)0;
  return string;
}
