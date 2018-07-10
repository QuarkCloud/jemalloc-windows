#include "test/jemalloc_test.h"

//btalloc_n_gen(1)
void * btalloc_1(size_t size, unsigned bits) 
{
	void *p;

	if (bits == 0) 
    {
		p = mallocx(size, 0);
	} 
    else 
    {			
		switch (bits & 0x1U) {
		case 0:	p = (btalloc_0(size, bits >> 1)); break;						
		case 1: p = (btalloc_1(size, bits >> 1)); break;						
		default: not_reached();
		}
	}
	assert_ptr_not_null(p, "Unexpected mallocx() failure");		
	return p;							
}
