
#ifndef __JEMALLOC_INTERNAL_ATOMIC_H
#define __JEMALLOC_INTERNAL_ATOMIC_H

#include <builtin.h>
#include <sys/types.h>
#include "jemalloc/internal/jemalloc_internal_macros.h"
#include "jemalloc/compile.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ATOMIC_INIT(...) {__VA_ARGS__}

typedef enum {
	atomic_memory_order_relaxed,
	atomic_memory_order_acquire,
	atomic_memory_order_release,
	atomic_memory_order_acq_rel,
	atomic_memory_order_seq_cst
} atomic_memory_order_t;


#define ATOMIC_RELAXED atomic_memory_order_relaxed
#define ATOMIC_ACQUIRE atomic_memory_order_acquire
#define ATOMIC_RELEASE atomic_memory_order_release
#define ATOMIC_ACQ_REL atomic_memory_order_acq_rel
#define ATOMIC_SEQ_CST atomic_memory_order_seq_cst

JEMALLOC_API int atomic_enum_to_builtin(atomic_memory_order_t mo) ;

JEMALLOC_INLINE void atomic_fence(atomic_memory_order_t mo) {__atomic_thread_fence(atomic_enum_to_builtin(mo)); }


typedef struct {
    void * repr ;
} atomic_p_t ;

JEMALLOC_INLINE void * atomic_load_p(const atomic_p_t *a , atomic_memory_order_t mo) 
{
    void * result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_p(atomic_p_t *a, void * val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE void * atomic_exchange_p(atomic_p_t *a, void * val,	atomic_memory_order_t mo) 
{
	void * result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_p(atomic_p_t *a, void * *expected, void * desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_p(atomic_p_t *a, void * *expected, void * desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}



typedef struct {
    bool repr ;
} atomic_b_t ;

JEMALLOC_INLINE bool atomic_load_b(const atomic_b_t * a , atomic_memory_order_t mo) 
{
    bool result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_b(atomic_b_t *a, bool val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE bool atomic_exchange_b(atomic_b_t *a, bool val,	atomic_memory_order_t mo) 
{
	bool result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_b(atomic_b_t *a, bool *expected, bool desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_b(atomic_b_t *a, bool * expected, bool desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}


typedef struct {
    unsigned int repr ;
} atomic_u_t ;

JEMALLOC_INLINE unsigned int atomic_load_u(const atomic_u_t * a , atomic_memory_order_t mo) 
{
    unsigned int result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_u(atomic_u_t *a, unsigned int val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE unsigned int atomic_exchange_u(atomic_u_t *a, unsigned int val,	atomic_memory_order_t mo) 
{
	unsigned int result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u(atomic_u_t *a, unsigned int *expected, unsigned int desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u(atomic_u_t *a, unsigned int * expected, unsigned int desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE unsigned int atomic_fetch_add_u(atomic_u_t *a, unsigned int val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE unsigned int atomic_fetch_sub_u(atomic_u_t *a, unsigned int val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE unsigned int atomic_fetch_and_u(atomic_u_t *a, unsigned int val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE unsigned int atomic_fetch_or_u(atomic_u_t *a, unsigned int val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE unsigned int atomic_fetch_xor_u(atomic_u_t *a, unsigned int val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}



typedef struct {
    size_t repr ;
} atomic_zu_t ;

JEMALLOC_INLINE size_t atomic_load_zu(const atomic_zu_t * a , atomic_memory_order_t mo) 
{
    size_t result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_zu(atomic_zu_t *a, size_t val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE size_t atomic_exchange_zu(atomic_zu_t *a, size_t val,	atomic_memory_order_t mo) 
{
	size_t result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_zu(atomic_zu_t *a, size_t *expected, size_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_zu(atomic_zu_t *a, size_t * expected, size_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE size_t atomic_fetch_add_zu(atomic_zu_t *a, size_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE size_t atomic_fetch_sub_zu(atomic_zu_t *a, size_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE size_t atomic_fetch_and_zu(atomic_zu_t *a, size_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE size_t atomic_fetch_or_zu(atomic_zu_t *a, size_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE size_t atomic_fetch_xor_zu(atomic_zu_t *a, size_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}



typedef struct {
    ssize_t repr ;
} atomic_zd_t ;

JEMALLOC_INLINE ssize_t atomic_load_zd(const atomic_zd_t * a , atomic_memory_order_t mo) 
{
    ssize_t result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_zd(atomic_zd_t *a, ssize_t val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE ssize_t atomic_exchange_zd(atomic_zd_t *a, ssize_t val,	atomic_memory_order_t mo) 
{
	ssize_t result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_zd(atomic_zd_t *a, ssize_t *expected, ssize_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_zd(atomic_zd_t *a, ssize_t * expected, ssize_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE ssize_t atomic_fetch_add_zd(atomic_zd_t *a, ssize_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE ssize_t atomic_fetch_sub_zd(atomic_zd_t *a, ssize_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE ssize_t atomic_fetch_and_zd(atomic_zd_t *a, ssize_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE ssize_t atomic_fetch_or_zd(atomic_zd_t *a, ssize_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE ssize_t atomic_fetch_xor_zd(atomic_zd_t *a, ssize_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}


typedef struct {
    uint8_t repr ;
} atomic_u8_t ;

JEMALLOC_INLINE uint8_t atomic_load_u8(const atomic_u8_t * a , atomic_memory_order_t mo) 
{
    uint8_t result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_u8(atomic_u8_t *a, uint8_t val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE uint8_t atomic_exchange_u8(atomic_u8_t *a, uint8_t val,	atomic_memory_order_t mo) 
{
	uint8_t result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u8(atomic_u8_t *a, uint8_t *expected, uint8_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u8(atomic_u8_t *a, uint8_t * expected, uint8_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE uint8_t atomic_fetch_add_u8(atomic_u8_t *a, uint8_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint8_t atomic_fetch_sub_u8(atomic_u8_t *a, uint8_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint8_t atomic_fetch_and_u8(atomic_u8_t *a, uint8_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint8_t atomic_fetch_or_u8(atomic_u8_t *a, uint8_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint8_t atomic_fetch_xor_u8(atomic_u8_t *a, uint8_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}


typedef struct {
    uint32_t repr ;
} atomic_u32_t ;

JEMALLOC_INLINE uint32_t atomic_load_u32(const atomic_u32_t * a , atomic_memory_order_t mo) 
{
    uint32_t result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_u32(atomic_u32_t *a, uint32_t val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE uint32_t atomic_exchange_u32(atomic_u32_t *a, uint32_t val,	atomic_memory_order_t mo) 
{
	uint32_t result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u32(atomic_u32_t *a, uint32_t *expected, uint32_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u32(atomic_u32_t *a, uint32_t * expected, uint32_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE uint32_t atomic_fetch_add_u32(atomic_u32_t *a, uint32_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint32_t atomic_fetch_sub_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint32_t atomic_fetch_and_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint32_t atomic_fetch_or_u32(atomic_u32_t *a, uint32_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint32_t atomic_fetch_xor_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}



typedef struct {
    uint64_t repr ;
} atomic_u64_t ;

JEMALLOC_INLINE uint64_t atomic_load_u64(const atomic_u64_t * a , atomic_memory_order_t mo) 
{
    uint64_t result ;
    __atomic_load(&a->repr, &result, atomic_enum_to_builtin(mo));
    return result ;
}

JEMALLOC_INLINE void atomic_store_u64(atomic_u64_t *a, uint64_t val , atomic_memory_order_t mo) 
{
	__atomic_store(&a->repr, &val, atomic_enum_to_builtin(mo));	
}

JEMALLOC_INLINE uint64_t atomic_exchange_u64(atomic_u64_t *a, uint64_t val,	atomic_memory_order_t mo) 
{
	uint64_t result;
	__atomic_exchange(&a->repr, &val, &result, atomic_enum_to_builtin(mo));
	return result;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u64(atomic_u64_t *a, uint64_t *expected, uint64_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,   true, 
        atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u64(atomic_u64_t *a, uint64_t * expected, uint64_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
	return __atomic_compare_exchange(&a->repr, expected, &desired,  false,
	    atomic_enum_to_builtin(success_mo), atomic_enum_to_builtin(failure_mo));
}

JEMALLOC_INLINE uint64_t atomic_fetch_add_u64(atomic_u64_t *a, uint64_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_add(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint64_t atomic_fetch_sub_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_sub(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint64_t atomic_fetch_and_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_and(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint64_t atomic_fetch_or_u64(atomic_u64_t *a, uint64_t val, atomic_memory_order_t mo) 
{
	return __atomic_fetch_or(&a->repr, val, atomic_enum_to_builtin(mo));
}

JEMALLOC_INLINE uint64_t atomic_fetch_xor_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
	return __atomic_fetch_xor(&a->repr, val,atomic_enum_to_builtin(mo));
}


#ifdef __cplusplus
}
#endif

#endif /* __JEMALLOC_INTERNAL_ATOMIC_H */
