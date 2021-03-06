/* Count characters in UTF-8 string.
   Copyright (C) 2007, 2009-2018 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2007.

   This program is free software: you can redistribute it and/or
   modify it under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at your
       option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at your
       option) any later version.

   or both in parallel, as here.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include "unistr.h"

size_t
u8_mbsnlen (const uint8_t *s, size_t n)
{
  size_t characters;

  characters = 0;
  while (n > 0)
    {
      ucs4_t uc;
      int count = u8_mbtoucr (&uc, s, n);
      characters++;
      if (count == -2)
        break;
      if (count < 0)
        count = u8_mbtouc (&uc, s, n);
      else if (count == 0)
        count = 1;
      s += count;
      n -= count;
    }
  return characters;
}
