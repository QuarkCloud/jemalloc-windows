
#include "opt_swap.h"


static bool         conf_opt_abort          = opt_abort;
static bool         conf_opt_abort_conf     = opt_abort_conf;
static const char * conf_opt_junk           = opt_junk;
static bool         conf_opt_junk_alloc     = opt_junk_alloc;
static bool         conf_opt_junk_free      = opt_junk_free;
static bool         conf_opt_utrace         = opt_utrace;
static bool         conf_opt_xmalloc        = opt_xmalloc;
static bool         conf_opt_zero           = opt_zero;
static unsigned     conf_opt_narenas        = opt_narenas;

static ssize_t      conf_opt_dirty_decay_ms = opt_dirty_decay_ms;
static ssize_t      conf_opt_muzzy_decay_ms = opt_muzzy_decay_ms;

static bool	        conf_opt_tcache         = opt_tcache;
static ssize_t	    conf_opt_lg_tcache_max  = opt_lg_tcache_max;
static unsigned	    conf_nhbins             = nhbins;
static size_t	    conf_tcache_maxclass    = tcache_maxclass;

static bool         conf_opt_background_thread   = opt_background_thread;
static size_t       conf_opt_max_background_threads = opt_max_background_threads;



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

    opt_dirty_decay_ms = conf_opt_dirty_decay_ms;
    opt_muzzy_decay_ms = conf_opt_muzzy_decay_ms;

    opt_tcache         = conf_opt_tcache;
    opt_lg_tcache_max  = conf_opt_lg_tcache_max;
    nhbins             = conf_nhbins;
    tcache_maxclass    = conf_tcache_maxclass;

    opt_background_thread = conf_opt_background_thread ;
    opt_max_background_threads = conf_opt_max_background_threads ;
    opt_narenas = conf_opt_narenas ;
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

    conf_opt_dirty_decay_ms = opt_dirty_decay_ms;
    conf_opt_muzzy_decay_ms = opt_muzzy_decay_ms;

    conf_opt_tcache         = opt_tcache;
    conf_opt_lg_tcache_max  = opt_lg_tcache_max;
    conf_nhbins             = nhbins;
    conf_tcache_maxclass    = tcache_maxclass;

    conf_opt_background_thread   = opt_background_thread;
    conf_opt_max_background_threads = opt_max_background_threads;
    conf_opt_narenas             = opt_narenas;
}

bool conf_match(const char * src , const char * dst) 
{
    if(src == dst)  return true ;
    if(src == NULL || dst == NULL) return false ;

    int idx = 0 ;
    while(true)
    {
        if(src[idx] != dst[idx])
            return false ;

        if(src[idx] == '\0')
            break ;
        ++idx ;
    }

    return true ;
}


