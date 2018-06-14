
#ifndef __JEMALLOC_INTERNAL_DECLS_H
#define __JEMALLOC_INTERNAL_DECLS_H 1

#include <math.h>

#  include <sys/param.h>
#  include <sys/mman.h>
#  if !defined(__pnacl__) && !defined(__native_client__)
#    include <sys/syscall.h>
#    if !defined(SYS_write) && defined(__NR_write)
#      define SYS_write __NR_write
#    endif
#    include <sys/uio.h>
#  endif
#  include <pthread.h>
#  include <signal.h>

#  ifdef JEMALLOC_GLIBC_MALLOC_HOOK
#    include <sched.h>
#  endif

#  include <errno.h>
#  include <sys/time.h>
#  include <time.h>

#include <sys/types.h>

#include <limits.h>
#ifndef SIZE_T_MAX
#  define SIZE_T_MAX	SIZE_MAX
#endif
#ifndef SSIZE_MAX
#  define SSIZE_MAX	((ssize_t)(SIZE_T_MAX >> 1))
#endif
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#ifndef offsetof
#  define offsetof(type, member)	((size_t)&(((type *)NULL)->member))
#endif
#include <string.h>
#include <strings.h>
#include <ctype.h>
#  include <unistd.h>

#include <fcntl.h>

#endif /* __JEMALLOC_INTERNAL_H */
