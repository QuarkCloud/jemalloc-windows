
#ifndef __JEMALLOC_TEST_OPT_SWAP_H
#define __JEMALLOC_TEST_OPT_SWAP_H 1

#include <quark_compile.h>

__BEGIN_DECLS

static const char * __opt_junk_true     = "true" ;
static const char * __opt_junk_false    = "false" ;
static const char * __opt_junk_alloc    = "alloc" ;
static const char * __opt_junk_free     = "free" ;


void opt_swap_from_conf() ;
void opt_swap_to_conf() ;

__END_DECLS

#endif /** __JEMALLOC_TEST_OPT_SWAP_H */
