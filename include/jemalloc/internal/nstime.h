#ifndef JEMALLOC_INTERNAL_NSTIME_H
#define JEMALLOC_INTERNAL_NSTIME_H

#include "../jemalloc.h"

/* Maximum supported number of seconds (~584 years). */
#define NSTIME_SEC_MAX KQU(18446744072)
#define NSTIME_ZERO_INITIALIZER {0}

typedef struct {
	uint64_t ns;
} nstime_t;

JEMALLOC_API void nstime_init(nstime_t *time, uint64_t ns);
JEMALLOC_API void nstime_init2(nstime_t *time, uint64_t sec, uint64_t nsec);
JEMALLOC_API uint64_t nstime_ns(const nstime_t *time);
JEMALLOC_API uint64_t nstime_sec(const nstime_t *time);
JEMALLOC_API uint64_t nstime_msec(const nstime_t *time);
JEMALLOC_API uint64_t nstime_nsec(const nstime_t *time);
JEMALLOC_API void nstime_copy(nstime_t *time, const nstime_t *source);
JEMALLOC_API int nstime_compare(const nstime_t *a, const nstime_t *b);
JEMALLOC_API void nstime_add(nstime_t *time, const nstime_t *addend);
JEMALLOC_API void nstime_iadd(nstime_t *time, uint64_t addend);
JEMALLOC_API void nstime_subtract(nstime_t *time, const nstime_t *subtrahend);
JEMALLOC_API void nstime_isubtract(nstime_t *time, uint64_t subtrahend);
JEMALLOC_API void nstime_imultiply(nstime_t *time, uint64_t multiplier);
JEMALLOC_API void nstime_idivide(nstime_t *time, uint64_t divisor);
JEMALLOC_API uint64_t nstime_divide(const nstime_t *time, const nstime_t *divisor);

typedef bool (nstime_monotonic_t)(void);
extern JEMALLOC_API nstime_monotonic_t * nstime_monotonic;

typedef bool (nstime_update_t)(nstime_t *);
extern JEMALLOC_API nstime_update_t * nstime_update;

#endif /* JEMALLOC_INTERNAL_NSTIME_H */
