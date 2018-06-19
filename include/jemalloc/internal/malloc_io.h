
#ifndef __JEMALLOC_INTERNAL_MALLOC_IO_H
#define __JEMALLOC_INTERNAL_MALLOC_IO_H


#include "../jemalloc.h"

#  include <inttypes.h>
#  include <sys/types.h>
#  include <stdarg.h>
#  include <unistd.h>

#  define FMTd32 PRId32
#  define FMTu32 PRIu32
#  define FMTx32 PRIx32
#  define FMTd64 PRId64
#  define FMTu64 PRIu64
#  define FMTx64 PRIx64
#  define FMTdPTR PRIdPTR
#  define FMTuPTR PRIuPTR
#  define FMTxPTR PRIxPTR
//#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Size of stack-allocated buffer passed to buferror(). */
#define BUFERROR_BUF		64

/*
 * Size of stack-allocated buffer used by malloc_{,v,vc}printf().  This must be
 * large enough for all possible uses within jemalloc.
 */
#define MALLOC_PRINTF_BUFSIZE	4096

JEMALLOC_API int buferror(int err, char *buf, size_t buflen);
JEMALLOC_API uintmax_t malloc_strtoumax(const char *  nptr, char ** endptr,  int base);
JEMALLOC_API void malloc_write(const char *s);

/*
 * malloc_vsnprintf() supports a subset of snprintf(3) that avoids floating
 * point math.
 */
JEMALLOC_API size_t malloc_vsnprintf(char *str, size_t size, const char *format,va_list ap);

JEMALLOC_API size_t __cdecl malloc_snprintf(char *str, size_t size, const char *format, ...);
/*
 * The caller can set write_cb and cbopaque to null to choose to print with the
 * je_malloc_message hook.
 */
JEMALLOC_API void malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque, const char *format, va_list ap);
JEMALLOC_API void malloc_cprintf(void (*write_cb)(void *, const char *), void *cbopaque,const char *format, ...) ;
JEMALLOC_API void malloc_printf(const char *format, ...) ;

static inline ssize_t malloc_write_fd(int fd, const void *buf, size_t count) 
{
	ssize_t result = (ssize_t)write(fd, buf,count);
	return (ssize_t)result;
}

static inline ssize_t
malloc_read_fd(int fd, void *buf, size_t count) {
#if defined(JEMALLOC_USE_SYSCALL) && defined(SYS_read)
	long result = syscall(SYS_read, fd, buf, count);
#else
	ssize_t result = read(fd, buf,
#ifdef _WIN32
	    (unsigned int)
#endif
	    count);
#endif
	return (ssize_t)result;
}

#ifdef __cplusplus
}
#endif

#endif /* __JEMALLOC_INTERNAL_MALLOC_IO_H */
