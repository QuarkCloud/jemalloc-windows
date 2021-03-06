
#include "test/jemalloc_test.h"
#include "microbench.h"

static uint64_t nwarmup = 1000 ;
static uint64_t niter   = 10000 ;

TEST_BEGIN(test_malloc_vs_mallocx) {
	compare_funcs(nwarmup, niter, "malloc",
	    malloc_free, "mallocx", mallocx_free);
}
TEST_END


TEST_BEGIN(test_free_vs_dallocx) {
	compare_funcs(nwarmup , niter , "free", malloc_free,
	    "dallocx", malloc_dallocx);
}
TEST_END

TEST_BEGIN(test_dallocx_vs_sdallocx) {
	compare_funcs(nwarmup , niter , "dallocx", malloc_dallocx,
	    "sdallocx", malloc_sdallocx);
}
TEST_END


TEST_BEGIN(test_mus_vs_sallocx) {
	compare_funcs(nwarmup, niter , "malloc_usable_size",
	    malloc_mus_free, "sallocx", malloc_sallocx_free);
}
TEST_END


TEST_BEGIN(test_sallocx_vs_nallocx) {
	compare_funcs(nwarmup , niter , "sallocx",
	    malloc_sallocx_free, "nallocx", malloc_nallocx_free);
}
TEST_END


int main(int argc , char * argv[]) 
{
    int result = test_no_reentrancy(
	    test_malloc_vs_mallocx,
	    test_free_vs_dallocx,
	    test_dallocx_vs_sdallocx,
	    test_mus_vs_sallocx ,
	    test_sallocx_vs_nallocx);


    //test_malloc_vs_mallocx() ;
    //test_free_vs_dallocx() ;
    //test_dallocx_vs_sdallocx() ;
    //test_mus_vs_sallocx() ;
    //test_sallocx_vs_nallocx() ;

    return result ;
}
