
#ifndef __JEMALLOC_INTERNAL_BACKGROUND_THREAD_EXTERNS_H
#define __JEMALLOC_INTERNAL_BACKGROUND_THREAD_EXTERNS_H 1

#include "jemalloc/compile.h"
#include "jemalloc/internal/background_thread_structs.h"

extern JEMALLOC_API bool opt_background_thread;
extern JEMALLOC_API size_t opt_max_background_threads;
extern JEMALLOC_API malloc_mutex_t background_thread_lock;
extern JEMALLOC_API atomic_u32_t background_thread_enabled_state;
extern JEMALLOC_API size_t n_background_threads;
extern JEMALLOC_API size_t max_background_threads;
extern JEMALLOC_API background_thread_info_t *background_thread_info;
extern JEMALLOC_API bool can_enable_background_thread;

JEMALLOC_API bool background_thread_create(tsd_t *tsd, unsigned arena_ind);
JEMALLOC_API bool background_threads_enable(tsd_t *tsd);
JEMALLOC_API bool background_threads_disable(tsd_t *tsd);
JEMALLOC_API void background_thread_interval_check(tsdn_t *tsdn, arena_t *arena,
    arena_decay_t *decay, size_t npages_new);
JEMALLOC_API void background_thread_prefork0(tsdn_t *tsdn);
JEMALLOC_API void background_thread_prefork1(tsdn_t *tsdn);
JEMALLOC_API void background_thread_postfork_parent(tsdn_t *tsdn);
JEMALLOC_API void background_thread_postfork_child(tsdn_t *tsdn);
JEMALLOC_API bool background_thread_stats_read(tsdn_t *tsdn,   background_thread_stats_t *stats);
JEMALLOC_API void background_thread_ctl_init(tsdn_t *tsdn);

#ifdef JEMALLOC_PTHREAD_CREATE_WRAPPER
extern JEMALLOC_API int pthread_create_wrapper(pthread_t *__restrict, const pthread_attr_t *,
    void *(*)(void *), void *__restrict);
#endif
JEMALLOC_API bool background_thread_boot0(void);
JEMALLOC_API bool background_thread_boot1(tsdn_t *tsdn);

#endif /* __ */
