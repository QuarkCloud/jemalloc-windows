
#ifndef __JEMALLOC_H
#define __JEMALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <strings.h>

#include "jemalloc/defines.h"
#include "jemalloc/compile.h"

#ifdef __cplusplus
extern "C" {
#endif

extern JEMALLOC_API const char	*je_malloc_conf ;
extern JEMALLOC_API void (*je_malloc_message)(void *cbopaque, const char *s);

JEMALLOC_API void *je_malloc(size_t size) ;

JEMALLOC_API void *je_calloc(size_t num, size_t size) ;
JEMALLOC_API int je_posix_memalign(void **memptr, size_t alignment, size_t size) ;
JEMALLOC_API void *je_aligned_alloc(size_t alignment, size_t size) ;
JEMALLOC_API void *je_realloc(void *ptr, size_t size) ;
JEMALLOC_API void je_free(void *ptr);
JEMALLOC_API void *je_mallocx(size_t size, int flags);
JEMALLOC_API void *je_rallocx(void *ptr, size_t size,int flags);
JEMALLOC_API size_t je_xallocx(void *ptr, size_t size,size_t extra, int flags);
JEMALLOC_API size_t je_sallocx(const void *ptr,int flags);
JEMALLOC_API void je_dallocx(void *ptr, int flags);
JEMALLOC_API void je_sdallocx(void *ptr, size_t size,int flags);
JEMALLOC_API size_t je_nallocx(size_t size, int flags) ;

JEMALLOC_API int je_mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
JEMALLOC_API int je_mallctlnametomib(const char *name,size_t *mibp, size_t *miblenp);
JEMALLOC_API int je_mallctlbymib(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
JEMALLOC_API void je_malloc_stats_print(void (*write_cb)(void *, const char *), void *je_cbopaque,const char *opts);
JEMALLOC_API size_t je_malloc_usable_size(void *ptr);

JEMALLOC_API void *je_memalign(size_t alignment, size_t size);
JEMALLOC_API void *je_valloc(size_t size);


#ifdef __cplusplus
}
#endif

#endif /* JEMALLOC_H */
