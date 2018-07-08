
#ifndef __JEMALLOC_TEST_OPT_SWAP_H
#define __JEMALLOC_TEST_OPT_SWAP_H 1

#include <quark_compile.h>
#include "jemalloc/internal/jemalloc_internal_externs.h"
#include "jemalloc/internal/arena_externs.h"
#include "jemalloc/internal/tcache_externs.h"
#include "jemalloc/internal/background_thread_externs.h"
#include "jemalloc/internal/prof_externs.h"

__BEGIN_DECLS

static const char * __opt_junk_true     = "true" ;
static const char * __opt_junk_false    = "false" ;
static const char * __opt_junk_alloc    = "alloc" ;
static const char * __opt_junk_free     = "free" ;


void opt_swap_from_conf() ;
void opt_swap_to_conf() ;

bool conf_match(const char * src , const char * dst) ;

__END_DECLS

#endif /** __JEMALLOC_TEST_OPT_SWAP_H */
