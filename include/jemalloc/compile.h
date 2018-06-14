#ifndef __JEMALLOC_COMPILE_H
#define __JEMALLOC_COMPILE_H 1


#ifdef JEMALLOC_EXPORT
    #define JEMALLOC_API __declspec(dllexport)
#else
    #define JEMALLOC_API __declspec(dllimport)
#endif

#define JEMALLOC_INLINE static inline


#endif /** __JEMALLOC_COMPILE_H */
