
#ifndef __JEMALLOC_INTERNAL_ARENA_EXTERNS_H
#define __JEMALLOC_INTERNAL_ARENA_EXTERNS_H 1

#include "jemalloc/internal/bin.h"
#include "jemalloc/internal/extent_dss.h"
#include "jemalloc/internal/hook.h"
#include "jemalloc/internal/pages.h"
#include "jemalloc/internal/size_classes.h"
#include "jemalloc/internal/stats.h"
#include "jemalloc/internal/smoothstep.h"
#include "jemalloc/internal/arena_stats.h"
#include "jemalloc/compile.h"

extern JEMALLOC_API ssize_t opt_dirty_decay_ms;
extern JEMALLOC_API ssize_t opt_muzzy_decay_ms;

extern JEMALLOC_API percpu_arena_mode_t opt_percpu_arena;
extern JEMALLOC_API const char *percpu_arena_mode_names[];

extern JEMALLOC_API const uint64_t h_steps[SMOOTHSTEP_NSTEPS];
extern JEMALLOC_API malloc_mutex_t arenas_lock;

JEMALLOC_API void arena_basic_stats_merge(tsdn_t *tsdn, arena_t *arena,
    unsigned *nthreads, const char **dss, ssize_t *dirty_decay_ms,
    ssize_t *muzzy_decay_ms, size_t *nactive, size_t *ndirty, size_t *nmuzzy);
JEMALLOC_API void arena_stats_merge(tsdn_t *tsdn, arena_t *arena, unsigned *nthreads,
    const char **dss, ssize_t *dirty_decay_ms, ssize_t *muzzy_decay_ms,
    size_t *nactive, size_t *ndirty, size_t *nmuzzy, arena_stats_t *astats,
    bin_stats_t *bstats, arena_stats_large_t *lstats);
JEMALLOC_API void arena_extents_dirty_dalloc(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent);

JEMALLOC_API size_t arena_slab_regind(extent_t *slab, szind_t binind, const void *ptr);

JEMALLOC_API extent_t *arena_extent_alloc_large(tsdn_t *tsdn, arena_t *arena,
    size_t usize, size_t alignment, bool *zero);
JEMALLOC_API void arena_extent_dalloc_large_prep(tsdn_t *tsdn, arena_t *arena,
    extent_t *extent);
JEMALLOC_API void arena_extent_ralloc_large_shrink(tsdn_t *tsdn, arena_t *arena,
    extent_t *extent, size_t oldsize);
JEMALLOC_API void arena_extent_ralloc_large_expand(tsdn_t *tsdn, arena_t *arena,
    extent_t *extent, size_t oldsize);
JEMALLOC_API ssize_t arena_dirty_decay_ms_get(arena_t *arena);
JEMALLOC_API bool arena_dirty_decay_ms_set(tsdn_t *tsdn, arena_t *arena, ssize_t decay_ms);
JEMALLOC_API ssize_t arena_muzzy_decay_ms_get(arena_t *arena);
JEMALLOC_API bool arena_muzzy_decay_ms_set(tsdn_t *tsdn, arena_t *arena, ssize_t decay_ms);
JEMALLOC_API void arena_decay(tsdn_t *tsdn, arena_t *arena, bool is_background_thread,
    bool all);
JEMALLOC_API void arena_reset(tsd_t *tsd, arena_t *arena);
JEMALLOC_API void arena_destroy(tsd_t *tsd, arena_t *arena);
JEMALLOC_API void arena_tcache_fill_small(tsdn_t *tsdn, arena_t *arena, tcache_t *tcache,
    cache_bin_t *tbin, szind_t binind, uint64_t prof_accumbytes);
JEMALLOC_API void arena_alloc_junk_small(void *ptr, const bin_info_t *bin_info,
    bool zero);

typedef void (arena_dalloc_junk_small_t)(void *, const bin_info_t *);
extern JEMALLOC_API arena_dalloc_junk_small_t *JET_MUTABLE arena_dalloc_junk_small;

JEMALLOC_API void *arena_malloc_hard(tsdn_t *tsdn, arena_t *arena, size_t size,
    szind_t ind, bool zero);
JEMALLOC_API void *arena_palloc(tsdn_t *tsdn, arena_t *arena, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache);
JEMALLOC_API void arena_prof_promote(tsdn_t *tsdn, const void *ptr, size_t usize);
JEMALLOC_API void arena_dalloc_promoted(tsdn_t *tsdn, void *ptr, tcache_t *tcache,
    bool slow_path);
JEMALLOC_API void arena_dalloc_bin_junked_locked(tsdn_t *tsdn, arena_t *arena,
    extent_t *extent, void *ptr);
JEMALLOC_API void arena_dalloc_small(tsdn_t *tsdn, void *ptr);
JEMALLOC_API bool arena_ralloc_no_move(tsdn_t *tsdn, void *ptr, size_t oldsize, size_t size,
    size_t extra, bool zero);
JEMALLOC_API void *arena_ralloc(tsdn_t *tsdn, arena_t *arena, void *ptr, size_t oldsize,
    size_t size, size_t alignment, bool zero, tcache_t *tcache,
    hook_ralloc_args_t *hook_args);
JEMALLOC_API dss_prec_t arena_dss_prec_get(arena_t *arena);
JEMALLOC_API bool arena_dss_prec_set(arena_t *arena, dss_prec_t dss_prec);
JEMALLOC_API ssize_t arena_dirty_decay_ms_default_get(void);
JEMALLOC_API bool arena_dirty_decay_ms_default_set(ssize_t decay_ms);
JEMALLOC_API ssize_t arena_muzzy_decay_ms_default_get(void);
JEMALLOC_API bool arena_muzzy_decay_ms_default_set(ssize_t decay_ms);
JEMALLOC_API bool arena_retain_grow_limit_get_set(tsd_t *tsd, arena_t *arena,
    size_t *old_limit, size_t *new_limit);
JEMALLOC_API unsigned arena_nthreads_get(arena_t *arena, bool internal);
JEMALLOC_API void arena_nthreads_inc(arena_t *arena, bool internal);
JEMALLOC_API void arena_nthreads_dec(arena_t *arena, bool internal);
JEMALLOC_API size_t arena_extent_sn_next(arena_t *arena);
JEMALLOC_API arena_t *arena_new(tsdn_t *tsdn, unsigned ind, extent_hooks_t *extent_hooks);
JEMALLOC_API void arena_boot(void);
JEMALLOC_API void arena_prefork0(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork1(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork2(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork3(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork4(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork5(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork6(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_prefork7(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_postfork_parent(tsdn_t *tsdn, arena_t *arena);
JEMALLOC_API void arena_postfork_child(tsdn_t *tsdn, arena_t *arena);

#endif /* __JEMALLOC_INTERNAL_ARENA_EXTERNS_H */
