
#ifndef __JEMALLOC_INTERNAL_HASH_H
#define __JEMALLOC_INTERNAL_HASH_H 1

#include "jemalloc/internal/assert.h"
#include "jemalloc/jemalloc.h"

/*
 * The following hash function is based on MurmurHash3, placed into the public
 * domain by Austin Appleby.  See https://github.com/aappleby/smhasher for
 * details.
 */

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t hash_rotl_32(uint32_t x, int8_t r) 
{
	return ((x << r) | (x >> (32 - r)));
}

static inline uint64_t hash_rotl_64(uint64_t x, int8_t r) 
{
	return ((x << r) | (x >> (64 - r)));
}

JEMALLOC_API uint32_t hash_get_block_32(const uint32_t *p, int i) ;

JEMALLOC_API uint64_t hash_get_block_64(const uint64_t *p, int i) ;

JEMALLOC_API uint32_t hash_fmix_32(uint32_t h) ;

JEMALLOC_API uint64_t hash_fmix_64(uint64_t k) ;

JEMALLOC_API uint32_t hash_x86_32(const void *key, int len, uint32_t seed) ;

JEMALLOC_API void hash_x86_128(const void *key, const int len, uint32_t seed, uint64_t r_out[2]) ;

JEMALLOC_API void hash_x64_128(const void *key, const int len, const uint32_t seed,  uint64_t r_out[2]) ;

JEMALLOC_API void hash(const void *key, size_t len, const uint32_t seed, size_t r_hash[2])  ;

#ifdef __cplusplus
}
#endif

#endif /* __JEMALLOC_INTERNAL_HASH_H */
