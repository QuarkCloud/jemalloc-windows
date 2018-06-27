
#ifndef __JEMALLOC_INTERNAL_BITMAP_H
#define __JEMALLOC_INTERNAL_BITMAP_H 1

#include "jemalloc/internal/size_classes.h"
#include "jemalloc/internal/arena_types.h"
#include "jemalloc/internal/bit_util.h"
#include "jemalloc/compile.h"

typedef unsigned long bitmap_t;
#define LG_SIZEOF_BITMAP	LG_SIZEOF_LONG
/* Maximum bitmap bit count is determined by number of extent size classes. */
#if LG_SLAB_MAXREGS > LG_CEIL_NSIZES 
#define LG_BITMAP_MAXBITS LG_SLAB_MAXREGS
#else
#  define LG_BITMAP_MAXBITS	LG_CEIL_NSIZES
#endif

#define BITMAP_MAXBITS		(ZU(1) << LG_BITMAP_MAXBITS)

/* Number of bits per group. */
#define LG_BITMAP_GROUP_NBITS		(LG_SIZEOF_BITMAP + 3)
#define BITMAP_GROUP_NBITS		(1U << LG_BITMAP_GROUP_NBITS)
#define BITMAP_GROUP_NBITS_MASK		(BITMAP_GROUP_NBITS-1)


/* Number of groups required to store a given number of bits. */
#define BITMAP_BITS2GROUPS(nbits)					\
    (((nbits) + BITMAP_GROUP_NBITS_MASK) >> LG_BITMAP_GROUP_NBITS)

/*
 * Number of groups required at a particular level for a given number of bits.
 */
#define BITMAP_GROUPS_L0(nbits)						\
    BITMAP_BITS2GROUPS(nbits)
#define BITMAP_GROUPS_L1(nbits)						\
    BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(nbits))
#define BITMAP_GROUPS_L2(nbits)						\
    BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS((nbits))))
#define BITMAP_GROUPS_L3(nbits)						\
    BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(		\
	BITMAP_BITS2GROUPS((nbits)))))
#define BITMAP_GROUPS_L4(nbits)						\
    BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS(		\
	BITMAP_BITS2GROUPS(BITMAP_BITS2GROUPS((nbits))))))

/*
 * Assuming the number of levels, number of groups required for a given number
 * of bits.
 */
#define BITMAP_GROUPS_1_LEVEL(nbits)					\
    BITMAP_GROUPS_L0(nbits)
#define BITMAP_GROUPS_2_LEVEL(nbits)					\
    (BITMAP_GROUPS_1_LEVEL(nbits) + BITMAP_GROUPS_L1(nbits))
#define BITMAP_GROUPS_3_LEVEL(nbits)					\
    (BITMAP_GROUPS_2_LEVEL(nbits) + BITMAP_GROUPS_L2(nbits))
#define BITMAP_GROUPS_4_LEVEL(nbits)					\
    (BITMAP_GROUPS_3_LEVEL(nbits) + BITMAP_GROUPS_L3(nbits))
#define BITMAP_GROUPS_5_LEVEL(nbits)					\
    (BITMAP_GROUPS_4_LEVEL(nbits) + BITMAP_GROUPS_L4(nbits))


#define BITMAP_GROUPS(nbits)	BITMAP_BITS2GROUPS(nbits)
#define BITMAP_GROUPS_MAX	BITMAP_BITS2GROUPS(BITMAP_MAXBITS)

#define BITMAP_INFO_INITIALIZER(nbits) {				\
	/* nbits. */							\
	nbits,								\
	/* ngroups. */							\
	BITMAP_BITS2GROUPS(nbits)					\
}

typedef struct bitmap_level_s {
	/* Offset of this level's groups within the array of groups. */
	size_t group_offset;
} bitmap_level_t;

typedef struct bitmap_info_s {
	/* Logical number of bits in bitmap (stored at bottom level). */
	size_t nbits;

	/* Number of groups necessary for nbits. */
	size_t ngroups;
} bitmap_info_t;

JEMALLOC_API void bitmap_info_init(bitmap_info_t *binfo, size_t nbits);
JEMALLOC_API void bitmap_init(bitmap_t *bitmap, const bitmap_info_t *binfo, bool fill);
JEMALLOC_API size_t bitmap_size(const bitmap_info_t *binfo);

JEMALLOC_API bool bitmap_full(bitmap_t *bitmap, const bitmap_info_t *binfo) ;

JEMALLOC_API bool bitmap_get(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) ;

JEMALLOC_API void bitmap_set(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) ;

JEMALLOC_API size_t bitmap_ffu(const bitmap_t *bitmap, const bitmap_info_t *binfo, size_t min_bit)  ;

JEMALLOC_API size_t bitmap_sfu(bitmap_t *bitmap, const bitmap_info_t *binfo) ;

JEMALLOC_API void bitmap_unset(bitmap_t *bitmap, const bitmap_info_t *binfo, size_t bit) ;

#endif /* __JEMALLOC_INTERNAL_BITMAP_H */
