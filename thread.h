/*
 * thread
 *
 *  Created on: Oct 1, 2013
 *      Author: bnr@gwu.edu
 */



#ifndef THREAD_
#define THREAD_

#define LWT_NULL ((lightweight_thread*)0)
#define TCB_SZ = 4096


typedef void *(*lwt_fn_t)(void *);

typedef enum {
	running,
	ready,
	waiting,
	start,
	done
} state_t;

typedef struct {
	unsigned int thread_id;
	unsigned int parent_id;
	state_t state;
	struct lightweight_thread *next_thread;
	int size;
	lwt_fn_t fn;
	void *params;
	unsigned int sp_init;
	unsigned int  sp;
	unsigned int ip;
	void *retval;

} lightweight_thread ;

typedef lightweight_thread *lwt_t;


lwt_t lwt_create(lwt_fn_t fn, void *data);
void *lwt_join(lwt_t);
void lwt_die(void *);
unsigned int lwt_yield(lwt_t);
lwt_t lwt_current(void);
unsigned int lwt_id(lwt_t);


//int __lwt_start(void);
void __lwt_start(lwt_fn_t fn, void *data);
//void __lwt_start(void);

void __lwt_schedule(void);
void __lwt_dispatch(lwt_t, lwt_t );
void __lwt_trampoline_inline(void);
lightweight_thread* __Runqueue_pop(lightweight_thread **Head);
unsigned int __Runqueue_add(lightweight_thread **list, lightweight_thread *thd_ptr);


#endif /* THREAD_ */
