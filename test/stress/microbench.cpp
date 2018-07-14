
#include "test/jemalloc_test.h"
#include "microbench.h"

void time_func(timedelta_t *timer, uint64_t nwarmup, uint64_t niter, void (*func)(void)) 
{
	uint64_t i;

	for (i = 0; i < nwarmup; i++) {
		func();
	}
	timer_start(timer);
	for (i = 0; i < niter; i++) {
		func();
	}
	timer_stop(timer);
}

void compare_funcs(uint64_t nwarmup, uint64_t niter, const char *name_a,
    void (*func_a)(), const char *name_b, void (*func_b)()) 
{
	timedelta_t timer_a, timer_b;
	char ratio_buf[6];
	void *p;

	p = mallocx(1, 0);
	if (p == NULL) {
		test_fail("Unexpected mallocx() failure");
		return;
	}

	time_func(&timer_a, nwarmup, niter, func_a);
	time_func(&timer_b, nwarmup, niter, func_b);

	timer_ratio(&timer_a, &timer_b, ratio_buf, sizeof(ratio_buf));
	malloc_printf("%"FMTu64" iterations, %s=%"FMTu64"us, %s=%"FMTu64"us, ratio=1:%s\n",
	    niter, name_a, timer_usec(&timer_a), name_b, timer_usec(&timer_b),ratio_buf);

	dallocx(p, 0);
}

void malloc_free(void) 
{
	/* The compiler can optimize away free(malloc(1))! */
	void *p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	free(p);
}

void mallocx_free(void) 
{
	void *p = mallocx(1, 0);
	if (p == NULL) {
		test_fail("Unexpected mallocx() failure");
		return;
	}
	free(p);
}


void malloc_dallocx(void) 
{
	void *p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	dallocx(p, 0);
}

void malloc_sdallocx(void) 
{
	void *p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	sdallocx(p, 1, 0);
}

void malloc_mus_free(void) 
{
	void *p;

	p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	malloc_usable_size(p);
	free(p);
}

void malloc_sallocx_free(void) 
{
	void *p;

	p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	if (sallocx(p, 0) < 1) {
		test_fail("Unexpected sallocx() failure");
	}
	free(p);
}

void malloc_nallocx_free(void) 
{
	void *p;

	p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	if (nallocx(1, 0) < 1) {
		test_fail("Unexpected nallocx() failure");
	}
	free(p);
}

