
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integration_test.h"


int main(int argc , char *argv[])
{
    
    return 0 ;
}

void do_test_failed()
{
    f_test_mallocx() ;
}

void do_test_passed()
{
    //2018-07-16
    //�����ڴ�������������ͨ��
    f_test_aligned_alloc() ;
    f_test_allocated() ;
    f_test_extent() ; 

}

