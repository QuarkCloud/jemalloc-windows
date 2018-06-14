
#ifndef __JEMALLOC_MANGLE_H
#define __JEMALLOC_MANGLE_H 1

/*
 * By default application code must explicitly refer to mangled symbol names,
 * so that it is possible to use jemalloc in conjunction with another allocator
 * in the same application.  Define JEMALLOC_MANGLE in order to cause automatic
 * name mangling that matches the API prefixing that happened as a result of
 * --with-mangling and/or --with-jemalloc-prefix configuration settings.
 */
#ifdef JEMALLOC_MANGLE
#  ifndef JEMALLOC_NO_DEMANGLE
#    define JEMALLOC_NO_DEMANGLE
#  endif
#  define aligned_alloc je_aligned_alloc
#  define calloc je_calloc
#  define dallocx je_dallocx
#  define free je_free
#  define mallctl je_mallctl
#  define mallctlbymib je_mallctlbymib
#  define mallctlnametomib je_mallctlnametomib
#  define malloc je_malloc
#  define malloc_conf je_malloc_conf
#  define malloc_message je_malloc_message
#  define malloc_stats_print je_malloc_stats_print
#  define malloc_usable_size je_malloc_usable_size
#  define mallocx je_mallocx
#  define nallocx je_nallocx
#  define posix_memalign je_posix_memalign
#  define rallocx je_rallocx
#  define realloc je_realloc
#  define sallocx je_sallocx
#  define sdallocx je_sdallocx
#  define xallocx je_xallocx
#  define memalign je_memalign
#  define valloc je_valloc
#endif


#endif /** __JEMALLOC_MANGLE_H*/
