
#ifndef __JEMALLOC_TEST_UNIT_TEST_H
#define __JEMALLOC_TEST_UNIT_TEST_H 1

#include <quark_compile.h>

__BEGIN_DECLS

int f_test_zero() ;
int f_test_nstime() ;
int f_test_ql() ;
int f_test_qr() ;
int f_test_rb() ;
int f_test_hash() ;
int f_test_log() ;
int f_test_seq()  ;
int f_test_math() ;
int f_test_rtree() ;
int f_test_size_classes() ;
int f_test_atomic() ;
int f_test_spin() ;
int f_test_ticker() ;
int f_test_bit_util() ;
int f_test_bitmap() ;
int f_test_div() ;
int f_test_base() ;
int f_test_decay() ;
int f_test_a0() ;
int f_test_emitter() ;
int f_test_mq() ;
int f_test_mtx() ;
int f_test_pack() ;
int f_test_pages() ;
int f_test_ph() ;
int f_test_prng() ;
int f_test_tsd() ;
int f_test_smoothstep()  ;
int f_test_stats()  ;
int f_test_arena_reset() ;
int f_test_background_thread() ;
int f_test_background_thread_enable() ;
int f_test_chk() ;
int f_test_extent_quantize() ;
int f_test_fork() ;
//2018-07-06
int f_test_hook() ;
int f_test_junk_true() ;
int f_test_mallctl() ;
int f_test_junk_alloc() ;
int f_test_junk_free() ;

int f_test_malloc_io(void) ;

//2017-08-10
int f_test_prof_accum(void) ;
int f_test_prof_active(void) ;
int f_test_prof_gdump(void) ;
int f_test_prof_idump(void) ;
int f_test_prof_reset(void) ;
int f_test_prof_tctx(void) ;

//2018-07-12
int f_test_prof_thread_name(void) ;
int f_test_retained(void) ;
int f_test_SFMT(void) ;
int f_test_slab(void) ;
int f_test_stats_print(void)  ;
int f_test_test_hooks() ;
int f_test_witness(void) ;

__END_DECLS

#endif /**__JEMALLOC_TEST_UNIT_TEST_H*/
