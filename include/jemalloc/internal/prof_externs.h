
#ifndef __JEMALLOC_INTERNAL_PROF_EXTERNS_H
#define __JEMALLOC_INTERNAL_PROF_EXTERNS_H 1

#include "jemalloc/internal/mutex.h"
#include "jemalloc/mangle.h"
#include "jemalloc/compile.h"

extern JEMALLOC_API malloc_mutex_t	bt2gctx_mtx;

extern JEMALLOC_API bool	opt_prof;
extern JEMALLOC_API bool	opt_prof_active;
extern JEMALLOC_API bool	opt_prof_thread_active_init;
extern JEMALLOC_API size_t	opt_lg_prof_sample;   /* Mean bytes between samples. */
extern JEMALLOC_API ssize_t	opt_lg_prof_interval; /* lg(prof_interval). */
extern JEMALLOC_API bool	opt_prof_gdump;       /* High-water memory dumping. */
extern JEMALLOC_API bool	opt_prof_final;       /* Final profile dumping. */
extern JEMALLOC_API bool	opt_prof_leak;        /* Dump leak summary at exit. */
extern JEMALLOC_API bool	opt_prof_accum;       /* Report cumulative bytes. */
extern JEMALLOC_API char	opt_prof_prefix[
    /* Minimize memory bloat for non-prof builds. */
#ifdef JEMALLOC_PROF
    PATH_MAX +
#endif
    1];

/* Accessed via prof_active_[gs]et{_unlocked,}(). */
extern JEMALLOC_API bool	prof_active;

/* Accessed via prof_gdump_[gs]et{_unlocked,}(). */
extern JEMALLOC_API bool	prof_gdump_val;

/*
 * Profile dump interval, measured in bytes allocated.  Each arena triggers a
 * profile dump when it reaches this threshold.  The effect is that the
 * interval between profile dumps averages prof_interval, though the actual
 * interval between dumps will tend to be sporadic, and the interval will be a
 * maximum of approximately (prof_interval * narenas).
 */
extern JEMALLOC_API uint64_t	prof_interval;

/*
 * Initialized as opt_lg_prof_sample, and potentially modified during profiling
 * resets.
 */
extern JEMALLOC_API size_t	lg_prof_sample;

JEMALLOC_API void prof_alloc_rollback(tsd_t *tsd, prof_tctx_t *tctx, bool updated);
JEMALLOC_API void prof_malloc_sample_object(tsdn_t *tsdn, const void *ptr, size_t usize,prof_tctx_t *tctx);
JEMALLOC_API void prof_free_sampled_object(tsd_t *tsd, size_t usize, prof_tctx_t *tctx);
JEMALLOC_API void bt_init(prof_bt_t *bt, void **vec);
JEMALLOC_API void prof_backtrace(prof_bt_t *bt);
JEMALLOC_API prof_tctx_t *prof_lookup(tsd_t *tsd, prof_bt_t *bt);

JEMALLOC_API size_t prof_tdata_count(void);
JEMALLOC_API size_t prof_bt_count(void);

typedef int (prof_dump_open_t)(bool, const char *);
extern JEMALLOC_API prof_dump_open_t *JET_MUTABLE prof_dump_open;

typedef bool (prof_dump_header_t)(tsdn_t *, bool, const prof_cnt_t *);
extern JEMALLOC_API prof_dump_header_t *JET_MUTABLE prof_dump_header;

JEMALLOC_API void prof_cnt_all(uint64_t *curobjs, uint64_t *curbytes, uint64_t *accumobjs,uint64_t *accumbytes);

JEMALLOC_API bool prof_accum_init(tsdn_t *tsdn, prof_accum_t *prof_accum);
JEMALLOC_API void prof_idump(tsdn_t *tsdn);
JEMALLOC_API bool prof_mdump(tsd_t *tsd, const char *filename);
JEMALLOC_API void prof_gdump(tsdn_t *tsdn);
JEMALLOC_API prof_tdata_t *prof_tdata_init(tsd_t *tsd);
JEMALLOC_API prof_tdata_t *prof_tdata_reinit(tsd_t *tsd, prof_tdata_t *tdata);
JEMALLOC_API void prof_reset(tsd_t *tsd, size_t lg_sample);
JEMALLOC_API void prof_tdata_cleanup(tsd_t *tsd);
JEMALLOC_API bool prof_active_get(tsdn_t *tsdn);
JEMALLOC_API bool prof_active_set(tsdn_t *tsdn, bool active);
JEMALLOC_API const char *prof_thread_name_get(tsd_t *tsd);
JEMALLOC_API int prof_thread_name_set(tsd_t *tsd, const char *thread_name);
JEMALLOC_API bool prof_thread_active_get(tsd_t *tsd);
JEMALLOC_API bool prof_thread_active_set(tsd_t *tsd, bool active);
JEMALLOC_API bool prof_thread_active_init_get(tsdn_t *tsdn);
JEMALLOC_API bool prof_thread_active_init_set(tsdn_t *tsdn, bool active_init);
JEMALLOC_API bool prof_gdump_get(tsdn_t *tsdn);
JEMALLOC_API bool prof_gdump_set(tsdn_t *tsdn, bool active);
JEMALLOC_API void prof_boot0(void);
JEMALLOC_API void prof_boot1(void);
JEMALLOC_API bool prof_boot2(tsd_t *tsd);
JEMALLOC_API void prof_prefork0(tsdn_t *tsdn);
JEMALLOC_API void prof_prefork1(tsdn_t *tsdn);
JEMALLOC_API void prof_postfork_parent(tsdn_t *tsdn);
JEMALLOC_API void prof_postfork_child(tsdn_t *tsdn);
JEMALLOC_API void prof_sample_threshold_update(prof_tdata_t *tdata);

#endif /* __JEMALLOC_INTERNAL_PROF_EXTERNS_H */
 