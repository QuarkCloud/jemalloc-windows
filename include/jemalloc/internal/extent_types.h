

#ifndef __JEMALLOC_INTERNAL_EXTENT_TYPES_H
#define __JEMALLOC_INTERNAL_EXTENT_TYPES_H 1

typedef struct extent_s extent_t;
typedef struct extents_s extents_t;

#define EXTENT_HOOKS_INITIALIZER	NULL

#define EXTENT_GROW_MAX_PIND (NPSIZES - 1)

/*
 * When reuse (and split) an active extent, (1U << opt_lg_extent_max_active_fit)
 * is the max ratio between the size of the active extent and the new extent.
 */
#define LG_EXTENT_MAX_ACTIVE_FIT_DEFAULT 6

#endif /* __JEMALLOC_INTERNAL_EXTENT_TYPES_H */
