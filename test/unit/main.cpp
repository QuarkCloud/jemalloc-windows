
#include "unit_test.h"

void do_test_failed() ;
void do_test_passed() ;


int main(int argc , char * argv[])
{
    f_test_decay() ;
    return 0 ;
}
void do_test_failed()
{
    f_test_decay() ;
    f_test_a0() ; 
    f_test_mq() ;
    f_test_pack() ; 
    f_test_ph() ; 
    f_test_tsd() ; 
    f_test_stats()  ;
    f_test_arena_reset() ;
}


void do_test_passed()
{
    f_test_nstime() ;
    f_test_ql() ;
    f_test_qr() ;
    f_test_hash() ;
    f_test_log() ;
    f_test_math() ;
    f_test_size_classes() ;
    f_test_atomic() ;
    f_test_spin() ;
    f_test_ticker() ;
    f_test_bit_util() ;
    f_test_bitmap() ;
    f_test_div() ;
    f_test_base() ;
    f_test_emitter() ;
    f_test_mtx() ;
    f_test_pages() ;
    f_test_prng() ;
    f_test_smoothstep()  ;

    //2018-06-22
    f_test_zero() ;
    f_test_rb() ;
    f_test_seq() ; 
    f_test_rtree() ;
}

