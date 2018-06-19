
#ifndef __JEMALLOC_TEST_JEMALLOC_TEST_DEFS_H
#define __JEMALLOC_TEST_JEMALLOC_TEST_DEFS_H 1

/* test/include/test/jemalloc_test_defs.h.  Generated from jemalloc_test_defs.h.in by configure.  */
#include "jemalloc/internal/jemalloc_internal_defs.h"
#include "jemalloc/internal/jemalloc_internal_decls.h"

/*
 * For use by SFMT.  configure.ac doesn't actually define HAVE_SSE2 because its
 * dependencies are notoriously unportable in practice.
 */
/* #undef HAVE_SSE2 */
/* #undef HAVE_ALTIVEC */

#ifdef TEST_EXPORTS
#define TESTAPI __declspec(dllexport)
#else 
#define TESTAPI __declspec(dllimport)
#endif

#endif /** __JEMALLOC_TEST_JEMALLOC_TEST_DEFS_H */

