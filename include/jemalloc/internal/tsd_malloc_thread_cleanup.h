
#ifndef __JEMALLOC_INTERNAL_TSD_MALLOC_THREAD_CLEANUP_H
#define __JEMALLOC_INTERNAL_TSD_MALLOC_THREAD_CLEANUP_H 1

#include "jemalloc/compile.h"

extern JEMALLOC_API tsd_t tsd_tls;
extern JEMALLOC_API bool tsd_initialized;
extern JEMALLOC_API bool tsd_booted;

/* Initialization/cleanup. */
JEMALLOC_ALWAYS_INLINE bool
tsd_cleanup_wrapper(void) {
	if (tsd_initialized) {
		tsd_initialized = false;
		tsd_cleanup(&tsd_tls);
	}
	return tsd_initialized;
}

JEMALLOC_ALWAYS_INLINE bool
tsd_boot0(void) {
	malloc_tsd_cleanup_register(&tsd_cleanup_wrapper);
	tsd_booted = true;
	return false;
}

JEMALLOC_ALWAYS_INLINE void
tsd_boot1(void) {
	/* Do nothing. */
}

JEMALLOC_ALWAYS_INLINE bool
tsd_boot(void) {
	return tsd_boot0();
}

JEMALLOC_ALWAYS_INLINE bool
tsd_booted_get(void) {
	return tsd_booted;
}

JEMALLOC_ALWAYS_INLINE bool
tsd_get_allocates(void) {
	return false;
}

/* Get/set. */
JEMALLOC_ALWAYS_INLINE tsd_t *
tsd_get(bool init) {
	assert(tsd_booted);
	return &tsd_tls;
}
JEMALLOC_ALWAYS_INLINE void
tsd_set(tsd_t *val) {
	assert(tsd_booted);
	if (likely(&tsd_tls != val)) {
		tsd_tls = (*val);
	}
	tsd_initialized = true;
}

#endif /** __JEMALLOC_INTERNAL_TSD_MALLOC_THREAD_CLEANUP_H */
