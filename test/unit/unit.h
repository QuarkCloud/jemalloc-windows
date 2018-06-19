
#ifndef __JEMALLOC_TEST_UNIT_H
#define __JEMALLOC_TEST_UNIT_H 1

#include "test/jemalloc_test.h"

__BEGIN_DECLS

void time_func(timedelta_t *timer, uint64_t nwarmup, uint64_t niter,   void (*func)(void)) ;

void compare_funcs(uint64_t nwarmup, uint64_t niter, const char *name_a,
    void (*func_a)(), const char *name_b, void (*func_b)()) ;

void malloc_free(void) ;

void mallocx_free(void) ;


void malloc_dallocx(void) ;

void malloc_sdallocx(void) ;

void malloc_mus_free(void) ;

void malloc_sallocx_free(void) ;

void malloc_nallocx_free(void) ;

__END_DECLS


#endif /**__JEMALLOC_TEST_UNIT_H*/
