
#include "test/jemalloc_test.h"
#include "unit_test.h"
#include "opt_swap.h"

static bool did_prof_dump_open;

static int
prof_dump_open_intercept(bool propagate_err, const char *filename) {
	int fd;

	did_prof_dump_open = true;

	fd = open("/dev/null", O_WRONLY);
	assert_d_ne(fd, -1, "Unexpected open() failure");

	return fd;
}

TEST_BEGIN(test_idump) {
	bool active;
	void *p;

	test_skip_if(!config_prof);

	active = true;
	assert_d_eq(mallctl("prof.active", NULL, NULL, (void *)&active,
	    sizeof(active)), 0,
	    "Unexpected mallctl failure while activating profiling");

	prof_dump_open = prof_dump_open_intercept;

	did_prof_dump_open = false;
	p = mallocx(1, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	dallocx(p, 0);
	assert_true(did_prof_dump_open, "Expected a profile dump");
}
TEST_END

int f_test_prof_idump(void) 
{
    opt_swap_to_conf() ;

    opt_tcache = false ;
    opt_prof = true ;
    opt_prof_accum = true ;
    opt_prof_active = false ;
    opt_lg_prof_sample = 0 ;
    opt_lg_prof_interval = 0 ;

	int result = test(test_idump);
    opt_swap_from_conf() ;
    return result ;
}
