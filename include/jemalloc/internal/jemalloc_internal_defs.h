

#ifndef __JEMALLOC_INTERNAL_DEFS_H
#define __JEMALLOC_INTERNAL_DEFS_H



#define CPU_SPINWAIT __asm {pause}
/* 1 if CPU_SPINWAIT is defined, 0 otherwise. */
#define HAVE_CPU_SPINWAIT 1

/*
 * Number of significant bits in virtual addresses.  This may be less than the
 * total number of bits in a pointer, e.g. on x64, for which the uppermost 16
 * bits are the same as bit 47.
 */
#define LG_VADDR 32

#define JEMALLOC_GCC_ATOMIC_ATOMICS 1


//#define JEMALLOC_HAVE_BUILTIN_CLZ 

/* Defined if syscall(2) is usable. */
#define JEMALLOC_USE_SYSCALL 

/*
 * Defined if secure_getenv(3) is available.
 */
#define JEMALLOC_HAVE_SECURE_GETENV 

/*
 * Defined if issetugid(2) is available.
 */
/* #undef JEMALLOC_HAVE_ISSETUGID */

/* Defined if pthread_atfork(3) is available. */
#define JEMALLOC_HAVE_PTHREAD_ATFORK 

/* Defined if pthread_setname_np(3) is available. */
//#define JEMALLOC_HAVE_PTHREAD_SETNAME_NP 

#define JEMALLOC_HAVE_CLOCK_MONOTONIC 1


/*
 * Defined if threaded initialization is known to be safe on this platform.
 * Among other things, it must be possible to initialize a mutex without
 * triggering allocation in order for threaded allocation to be safe.
 */
#define JEMALLOC_THREADED_INIT 

/* Non-empty if the tls_model attribute is supported. */
//#define JEMALLOC_TLS_MODEL //__attribute__((tls_model("initial-exec")))

/*
 * JEMALLOC_DEBUG enables assertions and other sanity checks, and disables
 * inline functions.
 */
#define JEMALLOC_DEBUG 

/* JEMALLOC_STATS enables statistics calculation. */
#define JEMALLOC_STATS 

/* JEMALLOC_PROF enables allocation profiling. */
#define JEMALLOC_PROF 

/*
 * JEMALLOC_DSS enables use of sbrk(2) to allocate extents from the data storage
 * segment (DSS).
 */
#define JEMALLOC_DSS 

/* Support memory filling (junk/zero). */
#define JEMALLOC_FILL 

/* One page is 2^LG_PAGE bytes. */
#define LG_PAGE 12

/*
 * One huge page is 2^LG_HUGEPAGE bytes.  Note that this is defined even if the
 * system does not explicitly support huge pages; system calls that require
 * explicit huge page support are separately configured.
 */
#define LG_HUGEPAGE 21

/*
 * If defined, adjacent virtual memory mappings with identical attributes
 * automatically coalesce, and they fragment when changes are made to subranges.
 * This is the normal order of things for mmap()/munmap(), but on Windows
 * VirtualAlloc()/VirtualFree() operations must be precisely matched, i.e.
 * mappings do *not* coalesce/fragment.
 */
#define JEMALLOC_MAPS_COALESCE 

/*
 * If defined, retain memory for later reuse by default rather than using e.g.
 * munmap() to unmap freed extents.  This is enabled on 64-bit Linux because
 * common sequences of mmap()/munmap() calls will cause virtual memory map
 * holes.
 */
#define JEMALLOC_RETAIN 

/* TLS is used to map arenas and magazine caches to threads. */
#define JEMALLOC_TLS 

/*
 * ffs*() functions to use for bitmapping.  Don't use these directly; instead,
 * use ffs_*() from util.h.
 */
#define JEMALLOC_INTERNAL_FFSLL __builtin_ffsll
#define JEMALLOC_INTERNAL_FFSL __builtin_ffsl
#define JEMALLOC_INTERNAL_FFS __builtin_ffs

/*
 * If defined, explicitly attempt to more uniformly distribute large allocation
 * pointer alignments across all cache indices.
 */
#define JEMALLOC_CACHE_OBLIVIOUS 


/* Defined if madvise(2) is available. */
#define JEMALLOC_HAVE_MADVISE 

/*
 * Defined if transparent huge pages are supported via the MADV_[NO]HUGEPAGE
 * arguments to madvise(2).
 */
//#define JEMALLOC_HAVE_MADVISE_HUGE 

/*
 * Methods for purging unused pages differ between operating systems.
 *
 *   madvise(..., MADV_FREE) : This marks pages as being unused, such that they
 *                             will be discarded rather than swapped out.
 *   madvise(..., MADV_DONTNEED) : If JEMALLOC_PURGE_MADVISE_DONTNEED_ZEROS is
 *                                 defined, this immediately discards pages,
 *                                 such that new pages will be demand-zeroed if
 *                                 the address region is later touched;
 *                                 otherwise this behaves similarly to
 *                                 MADV_FREE, though typically with higher
 *                                 system overhead.
 */
#define JEMALLOC_PURGE_MADVISE_FREE 
#define JEMALLOC_PURGE_MADVISE_DONTNEED 
#define JEMALLOC_PURGE_MADVISE_DONTNEED_ZEROS 

/* Defined if madvise(2) is available but MADV_FREE is not (x86 Linux only). */
#define JEMALLOC_DEFINE_MADVISE_FREE 

/* Define if operating system has alloca.h header. */
#define JEMALLOC_HAS_ALLOCA_H

/* C99 restrict keyword supported. */
#define JEMALLOC_HAS_RESTRICT 1

/* For use by hash code. */
/* #undef JEMALLOC_BIG_ENDIAN */

/* sizeof(int) == 2^LG_SIZEOF_INT. */
#define LG_SIZEOF_INT 2

/* sizeof(long) == 2^LG_SIZEOF_LONG. */
#define LG_SIZEOF_LONG 2

/* sizeof(long long) == 2^LG_SIZEOF_LONG_LONG. */
#define LG_SIZEOF_LONG_LONG 3

/* sizeof(intmax_t) == 2^LG_SIZEOF_INTMAX_T. */
#define LG_SIZEOF_INTMAX_T 3

/* glibc malloc hooks (__malloc_hook, __realloc_hook, __free_hook). */
#define JEMALLOC_GLIBC_MALLOC_HOOK 

/* glibc memalign hook. */
#define JEMALLOC_GLIBC_MEMALIGN_HOOK 

/* pthread support */
#define JEMALLOC_HAVE_PTHREAD 

/* dlsym() support */
#define JEMALLOC_HAVE_DLSYM 

/* Adaptive mutex support in pthreads. */
#define JEMALLOC_HAVE_PTHREAD_MUTEX_ADAPTIVE_NP 

/* GNU specific sched_getcpu support */
#define JEMALLOC_HAVE_SCHED_GETCPU 

/* GNU specific sched_setaffinity support */
#define JEMALLOC_HAVE_SCHED_SETAFFINITY 

/*
 * If defined, all the features necessary for background threads are present.
 */
#define JEMALLOC_BACKGROUND_THREAD 1


/* config.malloc_conf options string. */
#define JEMALLOC_CONFIG_MALLOC_CONF ""

/* If defined, jemalloc takes the malloc/free/etc. symbol names. */
#define JEMALLOC_IS_MALLOC 1

/*
 * Defined if strerror_r returns char * if _GNU_SOURCE is defined.
 */
#define JEMALLOC_STRERROR_R_RETURNS_CHAR_WITH_GNU_SOURCE 

#endif /* __JEMALLOC_INTERNAL_DEFS_H */
