#include "junk.cpp"


int f_test_junk_true(void) 
{
    opt_swap_to_conf() ;

    opt_abort = false ;
    opt_zero = false ;
    opt_junk = "ture" ;

	int result = test(
	    test_junk_small,
	    test_junk_large);

    opt_swap_from_conf() ;

    return result ;
}



