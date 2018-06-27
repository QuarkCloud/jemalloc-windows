#include "test/jemalloc_test.h"
#include "jemalloc/mangle.h"
#include "unit_test.h"

#define NSENDERS	3
#define NMSGS		10000


typedef struct mq_msg_s mq_msg_t;
typedef struct {
	mq_msg_t	*qre_next;
	mq_msg_t	*qre_prev;
} mq_msg_link_t ;

struct mq_msg_s {
	mq_msg_link_t link;
};

typedef struct {
	mq_msg_t *qlh_first;
} mq_head_t ;


typedef struct {							
	mtx_t		lock;					
	mq_head_t	msgs;					
	unsigned	count;					
} mq_t;

static bool	mq_init(mq_t *mq) 
{
									
	if (mtx_init(&mq->lock)) {					
		return true;						
	}								
	ql_new(&mq->msgs);						
	mq->count = 0;							
	return false;							
}									
static void mq_fini(mq_t *mq) 
{
	mtx_fini(&mq->lock);						
}									
static unsigned	mq_count(mq_t *mq) 
{
	unsigned count;							
									
	mtx_lock(&mq->lock);						
	count = mq->count;						
	mtx_unlock(&mq->lock);						
	return count;							
}									
static mq_msg_t * mq_tryget(mq_t *mq) 
{
	mq_msg_t *msg;						
									
	mtx_lock(&mq->lock);						
	msg = ql_first(&mq->msgs);					
	if (msg != NULL) {						
		ql_head_remove(&mq->msgs, mq_msg_t, link);	
		mq->count--;						
	}								
	mtx_unlock(&mq->lock);						
	return msg;							
}									
static mq_msg_t * mq_get(mq_t *mq) 
{
	mq_msg_t *msg;						
	unsigned ns;							
									
	msg = mq_tryget(mq);					
	if (msg != NULL) {						
		return msg;						
	}								
									
	ns = 1;								
	while (true) 
    {				
		mq_nanosleep(ns);					
		msg = mq_tryget(mq);				
		if (msg != NULL) {					
			return msg;					
		}							
		if (ns < 1000*1000*1000) {				
			/* Double sleep time, up to max 1 second. */	
			ns <<= 1;					
			if (ns > 1000*1000*1000) {			
				ns = 1000*1000*1000;			
			}						
		}							
	}								
}									
static void	mq_put(mq_t *mq, mq_msg_t *msg) 
{									
	mtx_lock(&mq->lock);						
	ql_elm_new(msg, link);					
	ql_tail_insert(&mq->msgs, msg, link);			
	mq->count++;							
	mtx_unlock(&mq->lock);						
}

TEST_BEGIN(test_mq_basic) {
	mq_t mq;
	mq_msg_t msg;

	assert_false(mq_init(&mq), "Unexpected mq_init() failure");
	assert_u_eq(mq_count(&mq), 0, "mq should be empty");
	assert_ptr_null(mq_tryget(&mq),
	    "mq_tryget() should fail when the queue is empty");

	mq_put(&mq, &msg);
	assert_u_eq(mq_count(&mq), 1, "mq should contain one message");
	assert_ptr_eq(mq_tryget(&mq), &msg, "mq_tryget() should return msg");

	mq_put(&mq, &msg);
	assert_ptr_eq(mq_get(&mq), &msg, "mq_get() should return msg");

	mq_fini(&mq);
}
TEST_END

static void *
thd_receiver_start(void *arg) {
	mq_t *mq = (mq_t *)arg;
	unsigned i;

	for (i = 0; i < (NSENDERS * NMSGS); i++) {
		mq_msg_t *msg = mq_get(mq);
		assert_ptr_not_null(msg, "mq_get() should never return NULL");
		dallocx(msg, 0);
	}
	return NULL;
}

static void *
thd_sender_start(void *arg) {
	mq_t *mq = (mq_t *)arg;
	unsigned i;

	for (i = 0; i < NMSGS; i++) {
		mq_msg_t *msg;
		void *p;
		p = mallocx(sizeof(mq_msg_t), 0);
		assert_ptr_not_null(p, "Unexpected mallocx() failure");
		msg = (mq_msg_t *)p;
		mq_put(mq, msg);
	}
	return NULL;
}

TEST_BEGIN(test_mq_threaded) {
	mq_t mq;
	thd_t receiver;
	thd_t senders[NSENDERS];
	unsigned i;

	assert_false(mq_init(&mq), "Unexpected mq_init() failure");

	thd_create(&receiver, thd_receiver_start, (void *)&mq);
	for (i = 0; i < NSENDERS; i++) {
		thd_create(&senders[i], thd_sender_start, (void *)&mq);
	}

	thd_join(receiver, NULL);
	for (i = 0; i < NSENDERS; i++) {
		thd_join(senders[i], NULL);
	}

	mq_fini(&mq);
}
TEST_END

int f_test_mq()
{

	return test(
	    test_mq_basic,
	    test_mq_threaded);

//	return test(test_mq_basic);
}

