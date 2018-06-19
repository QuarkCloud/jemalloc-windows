
#ifndef __JEMALLOC_TEST_THD_H
#define __JEMALLOC_TEST_THD_H 1

#include <quark_compile.h>
#include "test/jemalloc_test_defs.h"

__BEGIN_DECLS

typedef pthread_t thd_t;

TESTAPI void thd_create(thd_t *thd, void *(*proc)(void *), void *arg);
TESTAPI void thd_join(thd_t thd, void **ret);

__END_DECLS

#endif /** __JEMALLOC_TEST_THD_H*/
