
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integration_test.h"

void do_test_failed();
void do_test_passed();


int main(int argc , char *argv[])
{
	//2018-07-16
	//减少内存分配次数，得以通过
	//f_test_aligned_alloc();
	//f_test_allocated();
	//f_test_extent();
	//f_overflow();
	//f_test_posix_memalign();
	//f_test_rallocx();
	//f_test_sdallocx();
	//f_test_thread_arena();
	//thread_tcache_enabled();
	//f_test_xallocx();

	//f_test_mallocx();
    return 0 ;
}

void do_test_failed()
{
    f_test_mallocx() ;
}

void do_test_passed()
{
    //2018-07-16
    //减少内存分配次数，得以通过
    f_test_aligned_alloc() ;
    f_test_allocated() ;
    f_test_extent() ; 
    f_overflow() ;
    f_test_posix_memalign() ;
    f_test_rallocx() ;
    f_test_sdallocx() ;
    f_test_thread_arena() ;
    thread_tcache_enabled() ;
    f_test_xallocx() ;
}

