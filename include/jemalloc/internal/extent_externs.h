
#ifndef __JEMALLOC_INTERNAL_EXTENT_EXTERNS_H
#define __JEMALLOC_INTERNAL_EXTENT_EXTERNS_H 1

#include "jemalloc/internal/mutex.h"
#include "jemalloc/internal/mutex_pool.h"
#include "jemalloc/internal/ph.h"
#include "jemalloc/internal/rtree.h"
#include "jemalloc/compile.h"

extern JEMALLOC_API size_t opt_lg_extent_max_active_fit;

extern JEMALLOC_API rtree_t extents_rtree;
extern JEMALLOC_API const extent_hooks_t extent_hooks_default;
extern JEMALLOC_API mutex_pool_t extent_mutex_pool;

JEMALLOC_API extent_t *extent_alloc(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void extent_dalloc(tsdn_t *tsdn, arena_t *arena, extent_t *extent);

JEMALLOC_API extent_hooks_t *extent_hooks_get(arena_t *arena);
extent_hooks_t *extent_hooks_set(tsd_t *tsd, arena_t *arena,extent_hooks_t *extent_hooks);

JEMALLOC_API size_t extent_size_quantize_floor(size_t size);
JEMALLOC_API size_t extent_size_quantize_ceil(size_t size);

rb_proto(, extent_avail_, extent_tree_t, extent_t)
ph_proto(, extent_heap_, extent_heap_t, extent_t)

JEMALLOC_API bool extents_init(tsdn_t *tsdn, extents_t *extents, extent_state_t state,  bool delay_coalesce);
JEMALLOC_API extent_state_t extents_state_get(const extents_t *extents);
JEMALLOC_API size_t extents_npages_get(extents_t *extents);
JEMALLOC_API extent_t *extents_alloc(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extents_t *extents, void *new_addr,
    size_t size, size_t pad, size_t alignment, bool slab, szind_t szind,
    bool *zero, bool *commit);
JEMALLOC_API void extents_dalloc(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extents_t *extents, extent_t *extent);
JEMALLOC_API extent_t *extents_evict(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extents_t *extents, size_t npages_min);
JEMALLOC_API void extents_prefork(tsdn_t *tsdn, extents_t *extents);
JEMALLOC_API void extents_postfork_parent(tsdn_t *tsdn, extents_t *extents);
JEMALLOC_API void extents_postfork_child(tsdn_t *tsdn, extents_t *extents);
JEMALLOC_API extent_t *extent_alloc_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, void *new_addr, size_t size, size_t pad,
    size_t alignment, bool slab, szind_t szind, bool *zero, bool *commit);
JEMALLOC_API void extent_dalloc_gap(tsdn_t *tsdn, arena_t *arena, extent_t *extent);
JEMALLOC_API void extent_dalloc_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent);
JEMALLOC_API void extent_destroy_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent);
JEMALLOC_API bool extent_commit_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length);
JEMALLOC_API bool extent_decommit_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length);
JEMALLOC_API bool extent_purge_lazy_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length);
JEMALLOC_API bool extent_purge_forced_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length);
JEMALLOC_API extent_t *extent_split_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t size_a,
    szind_t szind_a, bool slab_a, size_t size_b, szind_t szind_b, bool slab_b);
JEMALLOC_API bool extent_merge_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *a, extent_t *b);

JEMALLOC_API bool extent_boot(void);

#endif /* __JEMALLOC_INTERNAL_EXTENT_EXTERNS_H */
