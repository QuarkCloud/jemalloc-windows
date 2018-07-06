#ifndef JEMALLOC_INTERNAL_LARGE_EXTERNS_H
#define JEMALLOC_INTERNAL_LARGE_EXTERNS_H

#include "jemalloc/internal/hook.h"
#include "jemalloc/compile.h"

JEMALLOC_API void *large_malloc(tsdn_t *tsdn, arena_t *arena, size_t usize, bool zero);
JEMALLOC_API void *large_palloc(tsdn_t *tsdn, arena_t *arena, size_t usize, size_t alignment,  bool zero);
JEMALLOC_API bool large_ralloc_no_move(tsdn_t *tsdn, extent_t *extent, size_t usize_min,size_t usize_max, bool zero);
JEMALLOC_API void *large_ralloc(tsdn_t *tsdn, arena_t *arena, void *ptr, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache,hook_ralloc_args_t *hook_args);

typedef void (large_dalloc_junk_t)(void *, size_t);
extern JEMALLOC_API large_dalloc_junk_t * large_dalloc_junk;

typedef void (large_dalloc_maybe_junk_t)(void *, size_t);
extern JEMALLOC_API  large_dalloc_maybe_junk_t * large_dalloc_maybe_junk;

JEMALLOC_API void large_dalloc_prep_junked_locked(tsdn_t *tsdn, extent_t *extent);
JEMALLOC_API void large_dalloc_finish(tsdn_t *tsdn, extent_t *extent);
JEMALLOC_API void large_dalloc(tsdn_t *tsdn, extent_t *extent);
JEMALLOC_API size_t large_salloc(tsdn_t *tsdn, const extent_t *extent);
JEMALLOC_API prof_tctx_t *large_prof_tctx_get(tsdn_t *tsdn, extent_t *extent);
JEMALLOC_API void large_prof_tctx_set(tsdn_t *tsdn, extent_t *extent, prof_tctx_t *tctx);
JEMALLOC_API void large_prof_tctx_reset(tsdn_t *tsdn, extent_t *extent);

#endif /* JEMALLOC_INTERNAL_LARGE_EXTERNS_H */
