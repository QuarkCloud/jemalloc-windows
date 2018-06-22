
#ifndef __JEMALLOC_INTERNAL_ARENA_STRUCTS_A_H
#define __JEMALLOC_INTERNAL_ARENA_STRUCTS_A_H 1

#include "jemalloc/internal/bitmap.h"

struct arena_slab_data_s {
	/* Per region allocated/deallocated bitmap. */
	bitmap_t	bitmap[BITMAP_GROUPS_MAX];
};

#endif /* __JEMALLOC_INTERNAL_ARENA_STRUCTS_A_H */
