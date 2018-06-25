
#ifndef __JEMALLOC_INTERNAL_TSD_DETAIL_H
#define __JEMALLOC_INTERNAL_TSD_DETAIL_H 1

#include "jemalloc/internal/arena_types.h"
#include "jemalloc/internal/assert.h"
#include "jemalloc/internal/jemalloc_internal_externs.h"
#include "jemalloc/internal/prof_types.h"
#include "jemalloc/internal/ql.h"
#include "jemalloc/internal/rtree_tsd.h"
#include "jemalloc/internal/tcache_types.h"
#include "jemalloc/internal/tcache_structs.h"
#include "jemalloc/internal/util.h"
#include "jemalloc/internal/witness.h"
#include "jemalloc/compile.h"




//JEMALLOC_ALWAYS_INLINE t * tsd_##n##p_get_unsafe(tsd_t *tsd) {return &tsd->TSD_MANGLE(n);}

JEMALLOC_ALWAYS_INLINE bool * tsd_tcache_enabledp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_tcache_enabled ;}
JEMALLOC_ALWAYS_INLINE bool * tsd_arenas_tdata_bypassp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_arenas_tdata_bypass ;}
JEMALLOC_ALWAYS_INLINE bool * tsd_in_hookp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_in_hook ;}
JEMALLOC_ALWAYS_INLINE int8_t * tsd_reentrancy_levelp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_reentrancy_level ;}
JEMALLOC_ALWAYS_INLINE uint32_t * tsd_narenas_tdatap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_narenas_tdata ;}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_offset_statep_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_offset_state ;}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_thread_allocatedp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_thread_allocated ;}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_thread_deallocatedp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_thread_deallocated ;}
JEMALLOC_ALWAYS_INLINE prof_tdata_t ** tsd_prof_tdatap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_prof_tdata ;}
JEMALLOC_ALWAYS_INLINE rtree_ctx_t * tsd_rtree_ctxp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_rtree_ctx ;}
JEMALLOC_ALWAYS_INLINE arena_t ** tsd_iarenap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_iarena ;}
JEMALLOC_ALWAYS_INLINE arena_t ** tsd_arenap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_arena ;}
JEMALLOC_ALWAYS_INLINE arena_tdata_t ** tsd_arenas_tdatap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_arenas_tdata ;}
JEMALLOC_ALWAYS_INLINE tsd_link_t * tsd_linkp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_link ;}
JEMALLOC_ALWAYS_INLINE tcache_t * tsd_tcachep_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_tcache ;}
JEMALLOC_ALWAYS_INLINE witness_tsd_t * tsd_witness_tsdp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_witness_tsd ;}
JEMALLOC_ALWAYS_INLINE int * tsd_test_datap_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_test_data ;}
JEMALLOC_ALWAYS_INLINE test_callback_t * tsd_test_callbackp_get_unsafe(tsd_t *tsd) {return &tsd->cant_access_tsd_items_directly_use_a_getter_or_setter_test_callback ;}

JEMALLOC_ALWAYS_INLINE bool tsd_state_validate(uint8_t state)
{
    if( state == tsd_state_nominal ||state == tsd_state_nominal_slow ||
        state == tsd_state_nominal_recompute ||	state == tsd_state_reincarnated ||
        state == tsd_state_minimal_initialized)
        return true ;
    else
        return false ;
}

JEMALLOC_ALWAYS_INLINE bool * tsd_tcache_enabledp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_tcache_enabledp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE bool * tsd_arenas_tdata_bypassp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_arenas_tdata_bypassp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE bool * tsd_in_hookp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_in_hookp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE int8_t * tsd_reentrancy_levelp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_reentrancy_levelp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE uint32_t * tsd_narenas_tdatap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_narenas_tdatap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_offset_statep_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_offset_statep_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_thread_allocatedp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_thread_allocatedp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE uint64_t * tsd_thread_deallocatedp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_thread_deallocatedp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE prof_tdata_t ** tsd_prof_tdatap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_prof_tdatap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE rtree_ctx_t * tsd_rtree_ctxp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_rtree_ctxp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE arena_t ** tsd_iarenap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_iarenap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE arena_t ** tsd_arenap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_arenap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE arena_tdata_t ** tsd_arenas_tdatap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_arenas_tdatap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE tsd_link_t * tsd_linkp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_linkp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE tcache_t * tsd_tcachep_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_tcachep_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE witness_tsd_t * tsd_witness_tsdp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_witness_tsdp_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE int * tsd_test_datap_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_test_datap_get_unsafe(tsd);
}
JEMALLOC_ALWAYS_INLINE test_callback_t * tsd_test_callbackp_get(tsd_t *tsd) 
{
	uint8_t state = tsd_state_get(tsd);
	assert(tsd_state_validate(state));
	return tsd_test_callbackp_get_unsafe(tsd);
}

//JEMALLOC_ALWAYS_INLINE t tsd_##n##_get(tsd_t *tsd) {return *tsd_##n##p_get(tsd);}
JEMALLOC_ALWAYS_INLINE bool tsd_tcache_enabled_get(tsd_t *tsd) {return *tsd_tcache_enabledp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE bool tsd_arenas_tdata_bypass_get(tsd_t *tsd) {return *tsd_arenas_tdata_bypassp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE bool tsd_in_hook_get(tsd_t *tsd) {return *tsd_in_hookp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE int8_t tsd_reentrancy_level_get(tsd_t *tsd) {return *tsd_reentrancy_levelp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE uint32_t tsd_narenas_tdata_get(tsd_t *tsd) {return *tsd_narenas_tdatap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE uint64_t tsd_offset_state_get(tsd_t *tsd) {return *tsd_offset_statep_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE uint64_t tsd_thread_allocated_get(tsd_t *tsd) {return *tsd_thread_allocatedp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE uint64_t tsd_thread_deallocated_get(tsd_t *tsd) {return *tsd_thread_deallocatedp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE prof_tdata_t *tsd_prof_tdata_get(tsd_t *tsd) {return *tsd_prof_tdatap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE rtree_ctx_t tsd_rtree_ctx_get(tsd_t *tsd) {return *tsd_rtree_ctxp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE arena_t *tsd_iarena_get(tsd_t *tsd) {return *tsd_iarenap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE arena_t *tsd_arena_get(tsd_t *tsd) {return *tsd_arenap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE arena_tdata_t *tsd_arenas_tdata_get(tsd_t *tsd) {return *tsd_arenas_tdatap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE tsd_link_t tsd_link_get(tsd_t *tsd) {return *tsd_linkp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE tcache_t tsd_tcache_get(tsd_t *tsd) {return *tsd_tcachep_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE witness_tsd_t tsd_witness_tsd_get(tsd_t *tsd) {return *tsd_witness_tsdp_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE int tsd_test_data_get(tsd_t *tsd) {return *tsd_test_datap_get(tsd) ;}
JEMALLOC_ALWAYS_INLINE test_callback_t tsd_test_callback_get(tsd_t *tsd) {return *tsd_test_callbackp_get(tsd) ;}


JEMALLOC_ALWAYS_INLINE bool *	tsdn_tcache_enabledp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (bool *)tsd_tcache_enabledp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE bool *	tsdn_arenas_tdata_bypassp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (bool *)tsd_arenas_tdata_bypassp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE bool *	tsdn_in_hookp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (bool *)tsd_in_hookp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE int8_t *	tsdn_reentrancy_levelp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (int8_t *)tsd_reentrancy_levelp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE uint32_t *	tsdn_narenas_tdatap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (uint32_t *)tsd_narenas_tdatap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE uint64_t *	tsdn_offset_statep_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (uint64_t *)tsd_offset_statep_get(tsd);
}

JEMALLOC_ALWAYS_INLINE uint64_t *	tsdn_thread_allocatedp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (uint64_t *)tsd_thread_allocatedp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE uint64_t *	tsdn_thread_deallocatedp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (uint64_t *)tsd_thread_deallocatedp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE prof_tdata_t**	tsdn_prof_tdatap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (prof_tdata_t* *)tsd_prof_tdatap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE rtree_ctx_t *	tsdn_rtree_ctxp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (rtree_ctx_t *)tsd_rtree_ctxp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE arena_t **	tsdn_iarenap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (arena_t **)tsd_iarenap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE arena_t **	tsdn_arenap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (arena_t **)tsd_arenap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE arena_tdata_t **	tsdn_arenas_tdatap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (arena_tdata_t **)tsd_arenas_tdatap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE tsd_link_t *	tsdn_linkp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (tsd_link_t *)tsd_linkp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE tcache_t *	tsdn_tcachep_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (tcache_t *)tsd_tcachep_get(tsd);
}

JEMALLOC_ALWAYS_INLINE witness_tsdn_t *	tsdn_witness_tsdp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (witness_tsdn_t *)tsd_witness_tsdp_get(tsd);
}

JEMALLOC_ALWAYS_INLINE int *	tsdn_test_datap_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (int *)tsd_test_datap_get(tsd);
}

JEMALLOC_ALWAYS_INLINE int *	tsdn_test_callbackp_get(tsdn_t *tsdn) 
{
    if (tsdn_null(tsdn)) 
    {
        return NULL;
    }
    tsd_t *tsd = tsdn_tsd(tsdn);
    return (int *)tsd_test_callbackp_get(tsd);
}


//tsd_state_get(tsd) != tsd_state_reincarnated && tsd_state_get(tsd) != tsd_state_minimal_initialized
JEMALLOC_ALWAYS_INLINE bool tsd_state_validate(tsd_t * tsd) {return (tsd_state_get(tsd) != tsd_state_reincarnated && tsd_state_get(tsd) != tsd_state_minimal_initialized) ;}

JEMALLOC_ALWAYS_INLINE void	 tsd_tcache_enabled_set(tsd_t *tsd,bool val){assert(tsd_state_validate(tsd));*tsd_tcache_enabledp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_arenas_tdata_bypass_set(tsd_t *tsd,bool val){assert(tsd_state_validate(tsd));*tsd_arenas_tdata_bypassp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_in_hook_set(tsd_t *tsd,bool val){assert(tsd_state_validate(tsd));*tsd_in_hookp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_reentrancy_level_set(tsd_t *tsd,int8_t val){assert(tsd_state_validate(tsd));*tsd_reentrancy_levelp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_narenas_tdata_set(tsd_t *tsd,uint32_t val){assert(tsd_state_validate(tsd));*tsd_narenas_tdatap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_offset_state_set(tsd_t *tsd,uint64_t val){assert(tsd_state_validate(tsd));*tsd_offset_statep_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_thread_allocated_set(tsd_t *tsd,uint64_t val){assert(tsd_state_validate(tsd));*tsd_thread_allocatedp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_thread_deallocated_set(tsd_t *tsd,uint64_t val){assert(tsd_state_validate(tsd));*tsd_thread_deallocatedp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_prof_tdata_set(tsd_t *tsd,prof_tdata_t * val){assert(tsd_state_validate(tsd));*tsd_prof_tdatap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_rtree_ctx_set(tsd_t *tsd,rtree_ctx_t val){assert(tsd_state_validate(tsd));*tsd_rtree_ctxp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_iarena_set(tsd_t *tsd,arena_t * val){assert(tsd_state_validate(tsd));*tsd_iarenap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_arena_set(tsd_t *tsd,arena_t * val){assert(tsd_state_validate(tsd));*tsd_arenap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_arenas_tdata_set(tsd_t *tsd,arena_tdata_t * val){assert(tsd_state_validate(tsd));*tsd_arenas_tdatap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_link_set(tsd_t *tsd,tsd_link_t val){assert(tsd_state_validate(tsd));*tsd_linkp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_tcache_set(tsd_t *tsd,tcache_t val){assert(tsd_state_validate(tsd));*tsd_tcachep_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_witness_tsd_set(tsd_t *tsd,witness_tsd_t val){assert(tsd_state_validate(tsd));*tsd_witness_tsdp_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_test_data_set(tsd_t *tsd,int val){assert(tsd_state_validate(tsd));*tsd_test_datap_get(tsd) =val;}
JEMALLOC_ALWAYS_INLINE void	 tsd_test_callback_set(tsd_t *tsd,test_callback_t val){assert(tsd_state_validate(tsd));*tsd_test_callbackp_get(tsd) =val;}





#endif /* __JEMALLOC_INTERNAL_TSD_DETAIL_H */
