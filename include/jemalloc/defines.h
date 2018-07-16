
#ifndef __JEMALLOC_DEFINES_H
#define __JEMALLOC_DEFINES_H 1


#include <builtin.h>
#  define ffsll(x) __builtin_ffsll(x)
#  define ffsl(x) __builtin_ffsl(x)
#  define ffs(x) __builtin_ffs(x)


/* sizeof(void *) == 2^LG_SIZEOF_PTR. */
#define LG_SIZEOF_PTR 2


#define JEMALLOC_VERSION "5.1.0-24-gd22e150320801c114b3694e860195254bad1ef0f"
#define JEMALLOC_VERSION_MAJOR 5
#define JEMALLOC_VERSION_MINOR 1
#define JEMALLOC_VERSION_BUGFIX 0
#define JEMALLOC_VERSION_NREV 24
#define JEMALLOC_VERSION_GID "d22e150320801c114b3694e860195254bad1ef0f"

#define MALLOCX_LG_ALIGN(la)	((int)(la))
#if LG_SIZEOF_PTR == 2
#  define MALLOCX_ALIGN(a)	((int)(ffs((int)(a))-1))
#else
#  define MALLOCX_ALIGN(a)						\
     ((int)(((size_t)(a) < (size_t)INT_MAX) ? ffs((int)(a))-1 :	\
     ffs((int)(((size_t)(a))>>32))+31))
#endif
#define MALLOCX_ZERO	((int)0x40)
/*
 * Bias tcache index bits so that 0 encodes "automatic tcache management", and 1
 * encodes MALLOCX_TCACHE_NONE.
 */
#define MALLOCX_TCACHE(tc)	((int)(((tc)+2) << 8))
#define MALLOCX_TCACHE_NONE	MALLOCX_TCACHE(-1)
/*
 * Bias arena index bits so that 0 encodes "use an automatically chosen arena".
 */
#define MALLOCX_ARENA(a)	((((int)(a))+1) << 20)

/*
 * Use as arena index in "arena.<i>.{purge,decay,dss}" and
 * "stats.arenas.<i>.*" mallctl interfaces to select all arenas.  This
 * definition is intentionally specified in raw decimal format to support
 * cpp-based string concatenation, e.g.
 *
 *   #define STRINGIFY_HELPER(x) #x
 *   #define STRINGIFY(x) STRINGIFY_HELPER(x)
 *
 *   mallctl("arena." STRINGIFY(MALLCTL_ARENAS_ALL) ".purge", NULL, NULL, NULL,
 *       0);
 */
#define MALLCTL_ARENAS_ALL	4096
/*
 * Use as arena index in "stats.arenas.<i>.*" mallctl interfaces to select
 * destroyed arenas.
 */
#define MALLCTL_ARENAS_DESTROYED	4097

#define JEMALLOC_ALIGNED(s) __declspec(align(s))
#define JEMALLOC_NOINLINE __declspec(noinline)
#define JEMALLOC_SECTION(s) __declspec(allocate(s))


#endif /** __JEMALLOC_DEFINES_H */
