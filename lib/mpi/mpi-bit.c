// SPDX-License-Identifier: GPL-2.0-or-later
/* mpi-bit.c  -  MPI bit level fucntions
 * Copyright (C) 1998, 1999 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 */

#include "mpi-internal.h"
#include "longlong.h"

#define A_LIMB_1 ((mpi_limb_t) 1)

/****************
 * Sometimes we have MSL (most significant limbs) which are 0;
 * this is for some reasons not good, so this function removes them.
 */
void mpi_normalize(MPI a)
{
	for (; a->nlimbs && !a->d[a->nlimbs - 1]; a->nlimbs--)
		;
}

/****************
 * Return the number of bits in A.
 */
unsigned mpi_get_nbits(MPI a)
{
	unsigned n;

	mpi_normalize(a);

	if (a->nlimbs) {
		mpi_limb_t alimb = a->d[a->nlimbs - 1];
		if (alimb)
			n = count_leading_zeros(alimb);
		else
			n = BITS_PER_MPI_LIMB;
		n = BITS_PER_MPI_LIMB - n + (a->nlimbs - 1) * BITS_PER_MPI_LIMB;
	} else
		n = 0;
	return n;
}
EXPORT_SYMBOL_GPL(mpi_get_nbits);
