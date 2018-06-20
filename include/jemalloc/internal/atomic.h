
#ifndef __JEMALLOC_INTERNAL_ATOMIC_H
#define __JEMALLOC_INTERNAL_ATOMIC_H 1

#include <atomic.h>
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
    void * volatile repr ;
} atomic_p_t ;

JEMALLOC_INLINE void * atomic_load_p(atomic_p_t *a , atomic_memory_order_t mo) 
{
    return ::atomic_load_ptr(&a->repr) ;
}

JEMALLOC_INLINE void atomic_store_p(atomic_p_t *a, void * val , atomic_memory_order_t mo) 
{
    ::atomic_store_ptr(&a->repr , val);
}

JEMALLOC_INLINE void * atomic_exchange_p(atomic_p_t *a, void * val,	atomic_memory_order_t mo) 
{
    return ::atomic_exchange_ptr(&a->repr , val) ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_p(atomic_p_t *a, void ** expected , void * desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    void * exp = *expected ;
    void * old = ::atomic_compare_exchange_ptr(&a->repr , exp , desired) ;
    if(old == exp)
        return true ;
    *expected = old ;
    return false ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_p(atomic_p_t *a, void ** expected, void * desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    return atomic_compare_exchange_weak_p(a , expected , desired , success_mo , failure_mo) ;
}


typedef struct {
    uint32_t volatile repr ;
} atomic_u32_t ;

JEMALLOC_INLINE uint32_t atomic_load_u32(atomic_u32_t * a , atomic_memory_order_t mo) 
{
    return ::atomic_load32(&a->repr) ;
}

JEMALLOC_INLINE void atomic_store_u32(atomic_u32_t *a, uint32_t val , atomic_memory_order_t mo) 
{
    ::atomic_store32(&a->repr , val) ;
}

JEMALLOC_INLINE uint32_t atomic_exchange_u32(atomic_u32_t *a, uint32_t val,	atomic_memory_order_t mo) 
{
    return ::atomic_exchange32(&a->repr , val) ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u32(atomic_u32_t *a, uint32_t *expected, uint32_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    uint32_t exp = *expected ;
    uint32_t old = ::atomic_compare_exchange32(&a->repr , exp , desired) ;
    if(old == exp)
        return true ;

    *expected = old ;
    return false ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u32(atomic_u32_t *a, uint32_t * expected, uint32_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    return atomic_compare_exchange_weak_u32(a , expected , desired , success_mo , failure_mo) ;
}

JEMALLOC_INLINE uint32_t atomic_fetch_add_u32(atomic_u32_t *a, uint32_t val, atomic_memory_order_t mo) 
{
    return ::atomic_fetch_add32(&a->repr , val) ;
}

JEMALLOC_INLINE uint32_t atomic_fetch_sub_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_sub32(&a->repr , val) ;
}

JEMALLOC_INLINE uint32_t atomic_fetch_and_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_and32(&a->repr , val) ;
}

JEMALLOC_INLINE uint32_t atomic_fetch_or_u32(atomic_u32_t *a, uint32_t val, atomic_memory_order_t mo) 
{
    return ::atomic_fetch_or32(&a->repr , val) ;
}

JEMALLOC_INLINE uint32_t atomic_fetch_xor_u32(atomic_u32_t *a, uint32_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_xor32(&a->repr , val) ;
}



typedef struct {
    volatile uint64_t repr ;
} atomic_u64_t ;

JEMALLOC_INLINE uint64_t atomic_load_u64(atomic_u64_t * a , atomic_memory_order_t mo) 
{
    return ::atomic_load64(&a->repr) ;
}

JEMALLOC_INLINE void atomic_store_u64(atomic_u64_t *a, uint64_t val , atomic_memory_order_t mo) 
{
    ::atomic_store64(&a->repr , val) ;
}

JEMALLOC_INLINE uint64_t atomic_exchange_u64(atomic_u64_t *a, uint64_t val,	atomic_memory_order_t mo) 
{
    return ::atomic_exchange64(&a->repr , val) ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_weak_u64(atomic_u64_t *a, uint64_t * expected, uint64_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    uint64_t exp = *expected ;
    uint64_t old = ::atomic_compare_exchange64(&a->repr , exp , desired) ;
    if(old == exp)
        return true ;

    *expected = old;
    return false ;
}

JEMALLOC_INLINE bool atomic_compare_exchange_strong_u64(atomic_u64_t *a, uint64_t * expected, uint64_t desired, 
    atomic_memory_order_t success_mo, atomic_memory_order_t failure_mo) 
{
    return atomic_compare_exchange_weak_u64(a , expected , desired , success_mo , failure_mo) ;
}

JEMALLOC_INLINE uint64_t atomic_fetch_add_u64(atomic_u64_t *a, uint64_t val, atomic_memory_order_t mo) 
{
    return ::atomic_fetch_add64(&a->repr , val) ;
}

JEMALLOC_INLINE uint64_t atomic_fetch_sub_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_sub64(&a->repr , val) ;
}

JEMALLOC_INLINE uint64_t atomic_fetch_and_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_and64(&a->repr , val) ;
}

JEMALLOC_INLINE uint64_t atomic_fetch_or_u64(atomic_u64_t *a, uint64_t val, atomic_memory_order_t mo) 
{
    return ::atomic_fetch_or64(&a->repr , val) ;
}

JEMALLOC_INLINE uint64_t atomic_fetch_xor_u64(atomic_u64_t *a, uint64_t val,atomic_memory_order_t mo) 
{
    return ::atomic_fetch_xor64(&a->repr , val) ;
}


#ifdef __cplusplus
}
#endif

#endif /* __JEMALLOC_INTERNAL_ATOMIC_H */
