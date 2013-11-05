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
	int thread_id;
	int parent_id;
	state_t state;
	struct lightweight_thread *next_thread;
	//struct lightweight_thread *prev_thread;
	int size;
	lwt_fn_t fn;
	void *params;
	void *stack;
	int sp_init;
	int  sp;
	int  ip;
	void *retval;

} lightweight_thread ;

typedef lightweight_thread *lwt_t;



lwt_t lwt_create(lwt_fn_t fn, void *data);
void *lwt_join(lwt_t);
void lwt_die(void *);
double lwt_yield(lwt_t);
lwt_t lwt_current(void);
double lwt_id(lwt_t);

void __lwt_schedule(void);
void __lwt_dispatch(lwt_t, lwt_t );
void __lwt_trampoline_inline(void);


double __Runqueue_add(lightweight_thread **a, lightweight_thread *b);
//int __Runqueue_remove(lwt_t);
lightweight_thread* __Runqueue_pop(lightweight_thread **Head);
//int __Waitqueue_add(lwt_t);
//int __Waitqueue_remove(lwt_t);

#endif /* THREAD_ */
