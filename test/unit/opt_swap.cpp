
#include "opt_swap.h"
#include "jemalloc/internal/jemalloc_internal_externs.h"
/**
extern JEMALLOC_API bool opt_abort;
extern JEMALLOC_API bool opt_abort_conf;
extern JEMALLOC_API const char *opt_junk;
extern JEMALLOC_API bool opt_junk_alloc;
extern JEMALLOC_API bool opt_junk_free;
extern JEMALLOC_API bool opt_utrace;
extern JEMALLOC_API bool opt_xmalloc;
extern JEMALLOC_API bool opt_zero;
extern JEMALLOC_API unsigned opt_narenas;
*/

static bool         conf_opt_abort          = opt_abort;
static bool         conf_opt_abort_conf     = opt_abort_conf;
static const char * conf_opt_junk           = opt_junk;
static bool         conf_opt_junk_alloc     = opt_junk_alloc;
static bool         conf_opt_junk_free      = opt_junk_free;
static bool         conf_opt_utrace         = opt_utrace;
static bool         conf_opt_xmalloc        = opt_xmalloc;
static bool         conf_opt_zero           = opt_zero;
static unsigned     conf_opt_narenas        = opt_narenas;


void opt_swap_from_conf()
{
    opt_abort          = conf_opt_abort;
    opt_abort_conf     = conf_opt_abort_conf;
    opt_junk           = conf_opt_junk;
    opt_junk_alloc     = conf_opt_junk_alloc;
    opt_junk_free      = conf_opt_junk_free;
    opt_utrace         = conf_opt_utrace;
    opt_xmalloc        = conf_opt_xmalloc;
    opt_zero           = conf_opt_zero;
    opt_narenas        = conf_opt_narenas;
}

void opt_swap_to_conf()
{
    conf_opt_abort          = opt_abort;
    conf_opt_abort_conf     = opt_abort_conf;
    conf_opt_junk           = opt_junk;
    conf_opt_junk_alloc     = opt_junk_alloc;
    conf_opt_junk_free      = opt_junk_free;
    conf_opt_utrace         = opt_utrace;
    conf_opt_xmalloc        = opt_xmalloc;
    conf_opt_zero           = opt_zero;
    conf_opt_narenas        = opt_narenas;
}

