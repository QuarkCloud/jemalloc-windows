
#include "jemalloc/internal/atomic.h"

int atomic_enum_to_builtin(atomic_memory_order_t mo) 
{
	switch (mo) {
	case atomic_memory_order_relaxed:
		return __ATOMIC_RELAXED;
	case atomic_memory_order_acquire:
		return __ATOMIC_ACQUIRE;
	case atomic_memory_order_release:
		return __ATOMIC_RELEASE;
	case atomic_memory_order_acq_rel:
		return __ATOMIC_ACQ_REL;
	case atomic_memory_order_seq_cst:
		return __ATOMIC_SEQ_CST;
	}
    return 0 ;
}

