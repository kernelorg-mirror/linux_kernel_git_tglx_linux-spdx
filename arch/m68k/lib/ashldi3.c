// SPDX-License-Identifier: GPL-2.0-or-later
/* ashrdi3.c extracted from gcc-2.95.2/libgcc2.c which is: */
/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

 */

#include <linux/compiler.h>
#include <linux/export.h>

#define BITS_PER_UNIT 8

typedef		 int SItype	__mode(SI);
typedef unsigned int USItype	__mode(SI);
typedef		 int DItype	__mode(DI);
typedef int word_type           __mode(__word__);

struct DIstruct {SItype high, low;};

typedef union
{
  struct DIstruct s;
  DItype ll;
} DIunion;

DItype
__ashldi3 (DItype u, word_type b)
{
  DIunion w;
  word_type bm;
  DIunion uu;

  if (b == 0)
    return u;

  uu.ll = u;

  bm = (sizeof (SItype) * BITS_PER_UNIT) - b;
  if (bm <= 0)
    {
      w.s.low = 0;
      w.s.high = (USItype)uu.s.low << -bm;
    }
  else
    {
      USItype carries = (USItype)uu.s.low >> bm;
      w.s.low = (USItype)uu.s.low << b;
      w.s.high = ((USItype)uu.s.high << b) | carries;
    }

  return w.ll;
}
EXPORT_SYMBOL(__ashldi3);
