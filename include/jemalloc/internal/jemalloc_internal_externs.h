
#ifndef __JEMALLOC_INTERNAL_EXTERNS_H
#define __JEMALLOC_INTERNAL_EXTERNS_H 1

#include "jemalloc/extent_hooks.h"
#include "jemalloc/internal/atomic.h"
#include "jemalloc/internal/size_classes.h"
#include "jemalloc/internal/tsd_types.h"
#include "jemalloc/compile.h"

/* TSD checks this to set thread local slow state accordingly. */
extern JEMALLOC_API bool malloc_slow;

/* Run-time options. */
extern JEMALLOC_API bool opt_abort;
extern JEMALLOC_API bool opt_abort_conf;
extern JEMALLOC_API const char *opt_junk;
extern JEMALLOC_API bool opt_junk_alloc;
extern JEMALLOC_API bool opt_junk_free;
extern JEMALLOC_API bool opt_utrace;
extern JEMALLOC_API bool opt_xmalloc;
extern JEMALLOC_API bool opt_zero;
extern JEMALLOC_API unsigned opt_narenas;

/* Number of CPUs. */
extern JEMALLOC_API unsigned ncpus;

/* Number of arenas used for automatic multiplexing of threads and arenas. */
extern JEMALLOC_API unsigned narenas_auto;

/*
 * Arenas that are used to service external requests.  Not all elements of the
 * arenas array are necessarily used; arenas are created lazily as needed.
 */
extern JEMALLOC_API atomic_p_t arenas[];

JEMALLOC_API void *a0malloc(size_t size);
JEMALLOC_API void a0dalloc(void *ptr);
JEMALLOC_API void *bootstrap_malloc(size_t size);
JEMALLOC_API void *bootstrap_calloc(size_t num, size_t size);
JEMALLOC_API void bootstrap_free(void *ptr);
JEMALLOC_API void arena_set(unsigned ind, arena_t *arena);
JEMALLOC_API unsigned narenas_total_get(void);
JEMALLOC_API arena_t *arena_init(tsdn_t *tsdn, unsigned ind, extent_hooks_t *extent_hooks);
JEMALLOC_API arena_tdata_t *arena_tdata_get_hard(tsd_t *tsd, unsigned ind);
JEMALLOC_API arena_t *arena_choose_hard(tsd_t *tsd, bool internal);
JEMALLOC_API void arena_migrate(tsd_t *tsd, unsigned oldind, unsigned newind);
JEMALLOC_API void iarena_cleanup(tsd_t *tsd);
JEMALLOC_API void arena_cleanup(tsd_t *tsd);
JEMALLOC_API void arenas_tdata_cleanup(tsd_t *tsd);
JEMALLOC_API void jemalloc_prefork(void);
JEMALLOC_API void jemalloc_postfork_parent(void);
JEMALLOC_API void jemalloc_postfork_child(void);
JEMALLOC_API bool malloc_initialized(void);

#endif /* __JEMALLOC_INTERNAL_EXTERNS_H */
