/*
 * mtx is a slightly simplified version of malloc_mutex.  This code duplication
 * is unfortunate, but there are allocator bootstrapping considerations that
 * would leak into the test infrastructure if malloc_mutex were used directly
 * in tests.
 */

typedef struct {
#if (defined(JEMALLOC_OS_UNFAIR_LOCK))
	os_unfair_lock		lock;
#elif (defined(JEMALLOC_OSSPIN))
	OSSpinLock		lock;
#else
	pthread_mutex_t		lock;
#endif
} mtx_t;

TESTAPI bool	mtx_init(mtx_t *mtx);
TESTAPI void	mtx_fini(mtx_t *mtx);
TESTAPI void	mtx_lock(mtx_t *mtx);
TESTAPI void	mtx_unlock(mtx_t *mtx);
