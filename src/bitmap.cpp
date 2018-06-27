#define JEMALLOC_BITMAP_C_
#include "jemalloc/internal/jemalloc_preamble.h"
#include "jemalloc/internal/jemalloc_internal_includes.h"
#include "jemalloc/internal/assert.h"
#include "jemalloc/internal/bitmap.h"


void bitmap_info_init(bitmap_info_t *binfo, size_t nbits) 
{
	assert(nbits > 0);
	assert(nbits <= (ZU(1) << LG_BITMAP_MAXBITS));

	binfo->ngroups = BITMAP_BITS2GROUPS(nbits);
	binfo->nbits = nbits;
}

static size_t bitmap_info_ngroups(const bitmap_info_t *binfo) 
{
	return binfo->ngroups;
}

void bitmap_init(bitmap_t *bitmap, const bitmap_info_t *binfo, bool fill) 
{
	size_t extra;

	if (fill) {
		memset(bitmap, 0, bitmap_size(binfo));
		return;
	}

	memset(bitmap, 0xffU, bitmap_size(binfo));
	extra = (BITMAP_GROUP_NBITS - (binfo->nbits & BITMAP_GROUP_NBITS_MASK))
	    & BITMAP_GROUP_NBITS_MASK;
	if (extra != 0) {
		bitmap[binfo->ngroups - 1] >>= extra;
	}
}

size_t bitmap_size(const bitmap_info_t *binfo) 
{
    size_t size = (bitmap_info_ngroups(binfo) << LG_SIZEOF_BITMAP);
	return size ;
}

bool bitmap_full(bitmap_t *bitmap, const bitmap_info_t *binfo) 
{
	size_t i;

	for (i = 0; i < binfo->ngroups; i++) {
		if (bitmap[i] != 0) {
			return false;
		}
	}
	return true;
}

bool bitmap_get(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) 
{
	size_t goff;
	bitmap_t g;

	assert(bit < binfo->nbits);
	goff = bit >> LG_BITMAP_GROUP_NBITS;
	g = bitmap[goff];
	return !(g & (ZU(1) << (bit & BITMAP_GROUP_NBITS_MASK)));
}

void bitmap_set(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) 
{
	size_t goff;
	bitmap_t *gp;
	bitmap_t g;

	assert(bit < binfo->nbits);
	assert(!bitmap_get(bitmap, binfo, bit));
	goff = bit >> LG_BITMAP_GROUP_NBITS;
	gp = &bitmap[goff];
	g = *gp;
	assert(g & (ZU(1) << (bit & BITMAP_GROUP_NBITS_MASK)));
	g ^= ZU(1) << (bit & BITMAP_GROUP_NBITS_MASK);
	*gp = g;
	assert(bitmap_get(bitmap, binfo, bit));
}

/* ffu: find first unset >= bit. */
size_t bitmap_ffu(const bitmap_t *bitmap, const bitmap_info_t *binfo, size_t min_bit) 
{
	assert(min_bit < binfo->nbits);

	size_t i = min_bit >> LG_BITMAP_GROUP_NBITS;
	bitmap_t g = bitmap[i] & ~((1LU << (min_bit & BITMAP_GROUP_NBITS_MASK))
	    - 1);
	size_t bit;
	do {
		bit = ffs_lu(g);
		if (bit != 0) {
			return (i << LG_BITMAP_GROUP_NBITS) + (bit - 1);
		}
		i++;
		g = bitmap[i];
	} while (i < binfo->ngroups);
	return binfo->nbits;
}

/* sfu: set first unset. */
size_t bitmap_sfu(bitmap_t *bitmap, const bitmap_info_t *binfo) 
{
	size_t bit;
	bitmap_t g;
	unsigned i;

	assert(!bitmap_full(bitmap, binfo));

	i = 0;
	g = bitmap[0];
	while ((bit = ffs_lu(g)) == 0) {
		i++;
		g = bitmap[i];
	}
	bit = (i << LG_BITMAP_GROUP_NBITS) + (bit - 1);
	bitmap_set(bitmap, binfo, bit);
	return bit;
}

void bitmap_unset(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) 
{
	size_t goff;
	bitmap_t *gp;
	bitmap_t g;
	bool propagate;

	assert(bit < binfo->nbits);
	assert(bitmap_get(bitmap, binfo, bit));
	goff = bit >> LG_BITMAP_GROUP_NBITS;
	gp = &bitmap[goff];
	g = *gp;
	propagate = (g == 0);
	assert((g & (ZU(1) << (bit & BITMAP_GROUP_NBITS_MASK))) == 0);
	g ^= ZU(1) << (bit & BITMAP_GROUP_NBITS_MASK);
	*gp = g;
	assert(!bitmap_get(bitmap, binfo, bit));
}
