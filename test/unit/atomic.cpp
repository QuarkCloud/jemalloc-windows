#include "test/jemalloc_test.h"
#include "unit_test.h"

/*
 * We *almost* have consistent short names (e.g. "u32" for uint32_t, "b" for
 * bool, etc.  The one exception is that the short name for void * is "p" in
 * some places and "ptr" in others.  In the long run it would be nice to unify
 * these, but in the short run we'll use this shim.
 */
#define assert_p_eq assert_ptr_eq

/*
 * t: the non-atomic type, like "uint32_t".
 * ta: the short name for the type, like "u32".
 * val[1,2,3]: Values of the given type.  The CAS tests use val2 for expected,
 * and val3 for desired.
 */
void do_test_u64(uint64_t val1 , uint64_t val2 , uint64_t val3) ;
void do_test_u32(uint32_t val1 , uint32_t val2 , uint32_t val3) ;
void do_test_p(void * val1 , void * val2 , void * val3) ;


void do_test_u64(uint64_t val1 , uint64_t val2 , uint64_t val3) 
{
	uint64_t val;								
	uint64_t expected;							
	bool success;							
	/* This (along with the load below) also tests ATOMIC_LOAD. */	
	atomic_u64_t atom = ATOMIC_INIT(val1);			
									
	/* ATOMIC_INIT and load. */					
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1, val, "Load or init failed");		
									
	/* Store. */							
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	atomic_store_u64(&atom, val2, ATOMIC_RELAXED);			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val2, val, "Store failed");			
									
	/* Exchange. */							
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_exchange_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val, "Exchange returned invalid value");	
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val2, val, "Exchange store invalid value");	
									
	/* 								
	 * Weak CAS.  Spurious failures are allowed, so we loop a few	
	 * times.							
	 */								
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	success = false;						
	for (int i = 0; i < 10 && !success; i++) {			
		expected = val2;					
		success = atomic_compare_exchange_weak_u64(&atom,	
		    &expected, val3, ATOMIC_RELAXED, ATOMIC_RELAXED);	
		assert_u64_eq(val1, expected, 			
		    "CAS should update expected");			
	}								
	assert_b_eq(val1 == val2, success,				
	    "Weak CAS did the wrong state update");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_u64_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_u64_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}								
									
	/* Strong CAS. */						
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	expected = val2;						
	success = atomic_compare_exchange_strong_u64(&atom, &expected,	
	    val3, ATOMIC_RELAXED, ATOMIC_RELAXED);			
	assert_b_eq(val1 == val2, success,				
	    "Strong CAS did the wrong state update");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_u64_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_u64_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}		
}

void do_test_u32(uint32_t val1 , uint32_t val2 , uint32_t val3) 
{
	uint32_t val;								
	uint32_t expected;							
	bool success;							
	/* This (along with the load below) also tests ATOMIC_LOAD. */	
	atomic_u32_t atom = ATOMIC_INIT(val1);			
									
	/* ATOMIC_INIT and load. */					
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1, val, "Load or init failed");		
									
	/* Store. */							
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	atomic_store_u32(&atom, val2, ATOMIC_RELAXED);			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val2, val, "Store failed");			
									
	/* Exchange. */							
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_exchange_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val, "Exchange returned invalid value");	
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val2, val, "Exchange store invalid value");	
									
	/* 								
	 * Weak CAS.  Spurious failures are allowed, so we loop a few	
	 * times.							
	 */								
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	success = false;						
	for (int i = 0; i < 10 && !success; i++) {			
		expected = val2;					
		success = atomic_compare_exchange_weak_u32(&atom,	
		    &expected, val3, ATOMIC_RELAXED, ATOMIC_RELAXED);	
		assert_u32_eq(val1, expected, 			
		    "CAS should update expected");			
	}								
	assert_b_eq(val1 == val2, success,				
	    "Weak CAS did the wrong state update");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_u32_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_u32_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}								
									
	/* Strong CAS. */						
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	expected = val2;						
	success = atomic_compare_exchange_strong_u32(&atom, &expected,	
	    val3, ATOMIC_RELAXED, ATOMIC_RELAXED);			
	assert_b_eq(val1 == val2, success,				
	    "Strong CAS did the wrong state update");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_u32_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_u32_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}
}

void do_test_p(void * val1 , void * val2 , void * val3) 
{
	void * val;								
	void * expected;							
	bool success;							
	/* This (along with the load below) also tests ATOMIC_LOAD. */	
	atomic_p_t atom = ATOMIC_INIT(val1);			
									
	/* ATOMIC_INIT and load. */					
	val = atomic_load_p(&atom, ATOMIC_RELAXED);			
	assert_p_eq(val1, val, "Load or init failed");		
									
	/* Store. */							
	atomic_store_p(&atom, val1, ATOMIC_RELAXED);			
	atomic_store_p(&atom, val2, ATOMIC_RELAXED);			
	val = atomic_load_p(&atom, ATOMIC_RELAXED);			
	assert_p_eq(val2, val, "Store failed");			
									
	/* Exchange. */							
	atomic_store_p(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_exchange_p(&atom, val2, ATOMIC_RELAXED);	
	assert_p_eq(val1, val, "Exchange returned invalid value");	
	val = atomic_load_p(&atom, ATOMIC_RELAXED);			
	assert_p_eq(val2, val, "Exchange store invalid value");	
									
	/* 								
	 * Weak CAS.  Spurious failures are allowed, so we loop a few	
	 * times.							
	 */								
	atomic_store_p(&atom, val1, ATOMIC_RELAXED);			
	success = false;						
	for (int i = 0; i < 10 && !success; i++) {			
		expected = val2;					
		success = atomic_compare_exchange_weak_p(&atom,	
		    &expected, val3, ATOMIC_RELAXED, ATOMIC_RELAXED);	
		assert_p_eq(val1, expected, 			
		    "CAS should update expected");			
	}								
	assert_b_eq(val1 == val2, success,				
	    "Weak CAS did the wrong state update");			
	val = atomic_load_p(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_p_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_p_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}								
									
	/* Strong CAS. */						
	atomic_store_p(&atom, val1, ATOMIC_RELAXED);			
	expected = val2;						
	success = atomic_compare_exchange_strong_p(&atom, &expected,	
	    val3, ATOMIC_RELAXED, ATOMIC_RELAXED);			
	assert_b_eq(val1 == val2, success,				
	    "Strong CAS did the wrong state update");			
	val = atomic_load_p(&atom, ATOMIC_RELAXED);			
	if (success) {							
		assert_p_eq(val3, val,				
		    "Successful CAS should update atomic");		
	} else {							
		assert_p_eq(val1, val,				
		    "Unsuccessful CAS should not update atomic");	
	}								
}

#define DO_TESTS(t, ta, val1, val2 , val3) do_test_##ta(val1 , val2 , val3)

//#define DO_INTEGER_TESTS(t, ta, val1, val2) 
void do_integer_test_u64(uint64_t val1 , uint64_t val2) ;
void do_integer_test_u32(uint32_t val1 , uint32_t val2) ;
void do_integer_test_p(void * val1 , void * val2) ;

void do_integer_test_u64(uint64_t val1 , uint64_t val2)
{
	atomic_u64_t atom;						
	uint64_t val;								
									
	/* Fetch-add. */						
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_add_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val,					
	    "Fetch-add should return previous value");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1 + val2, val,				
	    "Fetch-add should update atomic");				
									
	/* Fetch-sub. */						
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_sub_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val,					
	    "Fetch-sub should return previous value");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1 - val2, val,				
	    "Fetch-sub should update atomic");				
									
	/* Fetch-and. */						
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_and_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val,					
	    "Fetch-and should return previous value");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1 & val2, val,				
	    "Fetch-and should update atomic");				
									
	/* Fetch-or. */							
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_or_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val,					
	    "Fetch-or should return previous value");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1 | val2, val,				
	    "Fetch-or should update atomic");				
									
	/* Fetch-xor. */						
	atomic_store_u64(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_xor_u64(&atom, val2, ATOMIC_RELAXED);	
	assert_u64_eq(val1, val,					
	    "Fetch-xor should return previous value");			
	val = atomic_load_u64(&atom, ATOMIC_RELAXED);			
	assert_u64_eq(val1 ^ val2, val,				
	    "Fetch-xor should update atomic");				
}

void do_integer_test_u32(uint32_t val1 , uint32_t val2)
{
	atomic_u32_t atom;						
	uint32_t val;								
									
	/* Fetch-add. */						
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_add_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val,					
	    "Fetch-add should return previous value");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1 + val2, val,				
	    "Fetch-add should update atomic");				
									
	/* Fetch-sub. */						
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_sub_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val,					
	    "Fetch-sub should return previous value");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1 - val2, val,				
	    "Fetch-sub should update atomic");				
									
	/* Fetch-and. */						
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_and_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val,					
	    "Fetch-and should return previous value");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1 & val2, val,				
	    "Fetch-and should update atomic");				
									
	/* Fetch-or. */							
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_or_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val,					
	    "Fetch-or should return previous value");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1 | val2, val,				
	    "Fetch-or should update atomic");				
									
	/* Fetch-xor. */						
	atomic_store_u32(&atom, val1, ATOMIC_RELAXED);			
	val = atomic_fetch_xor_u32(&atom, val2, ATOMIC_RELAXED);	
	assert_u32_eq(val1, val,					
	    "Fetch-xor should return previous value");			
	val = atomic_load_u32(&atom, ATOMIC_RELAXED);			
	assert_u32_eq(val1 ^ val2, val,				
	    "Fetch-xor should update atomic");				
}

#define DO_INTEGER_TESTS(t, ta, val1, val2) do_integer_test_##ta(val1 , val2)


typedef struct {
    uint64_t val1 ;
    uint64_t val2 ;
    uint64_t val3 ;
} u64_test_t ;

typedef struct {
    uint32_t val1 ;
    uint32_t val2 ;
    uint32_t val3 ;
} u32_test_t ;

typedef struct {
    void * val1 ;
    void * val2 ;
    void * val3 ;
} p_test_t ;

#define TEST_STRUCT(t, ta)


#define TEST_CASES(t) {							\
	{(t)-1, (t)-1, (t)-2},						\
	{(t)-1, (t) 0, (t)-2},						\
	{(t)-1, (t) 1, (t)-2},						\
									\
	{(t) 0, (t)-1, (t)-2},						\
	{(t) 0, (t) 0, (t)-2},						\
	{(t) 0, (t) 1, (t)-2},						\
									\
	{(t) 1, (t)-1, (t)-2},						\
	{(t) 1, (t) 0, (t)-2},						\
	{(t) 1, (t) 1, (t)-2},						\
									\
	{(t)0, (t)-(1 << 22), (t)-2},					\
	{(t)0, (t)(1 << 22), (t)-2},					\
	{(t)(1 << 22), (t)-(1 << 22), (t)-2},				\
	{(t)(1 << 22), (t)(1 << 22), (t)-2}				\
}

#define TEST_BODY(t, ta) do {						\
	const ta##_test_t tests[] = TEST_CASES(t);			\
	for (unsigned i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {	\
		ta##_test_t test = tests[i];				\
		DO_TESTS(t, ta, test.val1, test.val2, test.val3);	\
	}								\
} while (0)

#define INTEGER_TEST_BODY(t, ta) do {					\
	const ta##_test_t tests[] = TEST_CASES(t);			\
	for (unsigned i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {	\
		ta##_test_t test = tests[i];				\
		DO_TESTS(t, ta, test.val1, test.val2, test.val3);	\
		DO_INTEGER_TESTS(t, ta, test.val1, test.val2);		\
	}								\
} while (0)

TEST_STRUCT(uint64_t, u64);
TEST_BEGIN(test_atomic_u64) {
	INTEGER_TEST_BODY(uint64_t, u64);
}
TEST_END


TEST_STRUCT(uint32_t, u32);
TEST_BEGIN(test_atomic_u32) {
	INTEGER_TEST_BODY(uint32_t, u32);
}
TEST_END

TEST_STRUCT(void *, p);
TEST_BEGIN(test_atomic_p) {
	TEST_BODY(void *, p);
}
TEST_END



int f_test_atomic(void) 
{
	return test(
	    test_atomic_u64,
	    test_atomic_u32,
	    test_atomic_p);
}
