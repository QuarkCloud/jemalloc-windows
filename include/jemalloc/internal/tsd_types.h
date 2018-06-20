#ifndef __JEMALLOC_INTERNAL_TSD_TYPES_H
#define __JEMALLOC_INTERNAL_TSD_TYPES_H 1

#define MALLOC_TSD_CLEANUPS_MAX	2

typedef struct tsd_s tsd_t;
typedef struct tsdn_s tsdn_t;
typedef bool (*malloc_tsd_cleanup_t)(void);

#endif /* __JEMALLOC_INTERNAL_TSD_TYPES_H */
