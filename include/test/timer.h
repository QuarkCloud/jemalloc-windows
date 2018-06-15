/* Simple timer, for use in benchmark reporting. */

typedef struct {
	nstime_t t0;
	nstime_t t1;
} timedelta_t;

TESTAPI void	timer_start(timedelta_t *timer);
TESTAPI void	timer_stop(timedelta_t *timer);
TESTAPI uint64_t	timer_usec(const timedelta_t *timer);
TESTAPI void	timer_ratio(timedelta_t *a, timedelta_t *b, char *buf, size_t buflen);
