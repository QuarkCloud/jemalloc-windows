#ifndef __JEMALLOC_INTERNAL_BASE_EXTERNS_H
#define __JEMALLOC_INTERNAL_BASE_EXTERNS_H

#include "jemalloc/compile.h"

extern JEMALLOC_API metadata_thp_mode_t opt_metadata_thp;
extern JEMALLOC_API const char *metadata_thp_mode_names[];


JEMALLOC_API base_t *b0get(void);

JEMALLOC_API base_t *base_new(tsdn_t *tsdn, unsigned ind, extent_hooks_t *extent_hooks);

JEMALLOC_API void base_delete(tsdn_t *tsdn, base_t *base);

JEMALLOC_API extent_hooks_t *base_extent_hooks_get(base_t *base);

JEMALLOC_API extent_hooks_t *base_extent_hooks_set(base_t *base,  extent_hooks_t *extent_hooks);

JEMALLOC_API void *base_alloc(tsdn_t *tsdn, base_t *base, size_t size, size_t alignment);

JEMALLOC_API extent_t *base_alloc_extent(tsdn_t *tsdn, base_t *base);

JEMALLOC_API void base_stats_get(tsdn_t *tsdn, base_t *base, size_t *allocated, size_t *resident, size_t *mapped, size_t *n_thp);

JEMALLOC_API void base_prefork(tsdn_t *tsdn, base_t *base);

JEMALLOC_API void base_postfork_parent(tsdn_t *tsdn, base_t *base);

JEMALLOC_API void base_postfork_child(tsdn_t *tsdn, base_t *base);

JEMALLOC_API bool base_boot(tsdn_t *tsdn);

#endif /* __JEMALLOC_INTERNAL_BASE_EXTERNS_H */
