
#ifndef __JEMALLOC_TEST_INTEGRATION_TEST_H
#define __JEMALLOC_TEST_INTEGRATION_TEST_H 1

#include <quark_compile.h>

__BEGIN_DECLS


int f_test_aligned_alloc() ;
int f_test_allocated(void) ;
int f_test_extent(void) ;
int f_test_mallocx(void) ;
int f_overflow(void) ;
int f_test_posix_memalign(void) ;
int f_test_rallocx(void) ;
int f_test_sdallocx(void) ;
int f_test_thread_arena(void) ;
int thread_tcache_enabled(void) ;
int f_test_xallocx(void) ;

__END_DECLS

#endif  /** __JEMALLOC_TEST_INTEGRATION_TEST_H */
