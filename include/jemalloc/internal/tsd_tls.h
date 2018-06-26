#ifndef __JEMALLOC_INTERNAL_TSD_TLS_H
#define __JEMALLOC_INTERNAL_TSD_TLS_H 1

#include "jemalloc/compile.h"
/**
    tsd_tls是线程变量，既每个线程有一个独立的存储。在高版本的编译器中，
    有__thread前缀修饰，在vs中C语言版本没有这样的修饰。在这里借鉴errno
    的处理模式。
*/
//extern JEMALLOC_API tsd_t tsd_tls ;
extern JEMALLOC_API tsd_t * __tsd_tls() ;
#define tsd_tls (*__tsd_tls())

extern JEMALLOC_API pthread_key_t tsd_tsd;
extern JEMALLOC_API bool tsd_booted ;

/* Initialization/cleanup. */
JEMALLOC_ALWAYS_INLINE bool tsd_boot0(void) 
{
	if (pthread_key_create(&tsd_tsd, &tsd_cleanup) != 0) {
		return true;
	}
	tsd_booted = true;
	return false;
}

JEMALLOC_ALWAYS_INLINE void tsd_boot1(void) 
{
	/* Do nothing. */
}

JEMALLOC_ALWAYS_INLINE bool tsd_boot(void) 
{
	return tsd_boot0();
}

JEMALLOC_ALWAYS_INLINE bool tsd_booted_get(void) 
{
	return tsd_booted;
}

JEMALLOC_ALWAYS_INLINE bool tsd_get_allocates(void) 
{
	return false;
}

/* Get/set. */
JEMALLOC_ALWAYS_INLINE tsd_t * tsd_get(bool init) 
{
	assert(tsd_booted);
	return &tsd_tls;
}

JEMALLOC_ALWAYS_INLINE void tsd_set(tsd_t *val) 
{
	assert(tsd_booted);
	if (likely(&tsd_tls != val)) {
		tsd_tls = (*val);
	}
	if (pthread_setspecific(tsd_tsd, (void *)(&tsd_tls)) != 0) {
		malloc_write("<jemalloc>: Error setting tsd.\n");
		if (opt_abort) {
			abort();
		}
	}
}


#endif /** __JEMALLOC_INTERNAL_TSD_TLS_H*/
