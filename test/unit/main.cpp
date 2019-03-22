
#include "unit_test.h"

void do_test_failed() ;


int main(int argc , char * argv[])
{ 
	/**
		2019-03-18
		以下每个测试在原代码中，是以单独进程的方式独立运行的，所以存在上次遗留的状态，
		影响下一个测试的问题。因此每次只能运行一个测试函数才可以。
	*/
	//f_test_nstime();
	//f_test_ql();
	//f_test_qr();
	//f_test_hash();
	//f_test_log();
	//f_test_math();
	//f_test_size_classes();
	//f_test_spin();
	//f_test_ticker();
	//f_test_bit_util();
	//f_test_bitmap();
	//f_test_div();

	//f_test_base();
	//f_test_emitter();
	//f_test_mtx();
	//f_test_pages();
	//f_test_prng();
	//f_test_smoothstep();

	////2018-06-22
	//f_test_zero();
	//f_test_rb();
	//f_test_seq();
	//f_test_rtree();

	////2018-06-27
	//f_test_decay();
	//f_test_a0();
	//f_test_mq();
	//f_test_pack();
	//f_test_ph();

	////2018-07-02
	//f_test_tsd();
	//f_test_stats();
	//f_test_arena_reset();

	////2018-07-04
	//f_test_background_thread();
	//f_test_atomic();
	//f_test_background_thread_enable();
	//f_test_chk();
	//f_test_extent_quantize();

	////2018-07-06
	//f_test_hook();
	//f_test_junk_true();
	//f_test_junk_alloc();
	//f_test_junk_free();
	//f_test_mallctl();

	//f_test_malloc_io();

	////2018-07-10
	//f_test_prof_active();
	//f_test_prof_gdump();
	//f_test_prof_idump();
	//f_test_prof_reset();

	////2018-07-12
	//f_test_prof_thread_name();
	//f_test_retained();
	//f_test_SFMT();
	//f_test_slab();
	//failed f_test_stats_print();
	//f_test_test_hooks();
	//f_test_witness();

	////2018-07-13
	//f_test_prof_tctx();
	f_test_prof_accum();
    return 0 ;
}
void do_test_failed()
{
    f_test_fork() ; 
    f_test_prof_accum() ;  
}

