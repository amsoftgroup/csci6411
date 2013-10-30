/*
 * thread
 *
 *  Created on: Oct 1, 2013
 *      Author: bnr@gwu.edu
 */

#ifndef THREAD_
#define THREAD_

#define LWT_NULL = (struct thread *)0
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
	struct lightweight_thread *prev_thread;
	int size;

	lwt_fn_t fn;
	void *params;

	void *stack;
	unsigned int sp_init;
	unsigned int sp;
	unsigned int ip;

} lightweight_thread ;

typedef lightweight_thread *lwt_t;

lwt_t lwt_create(lwt_fn_t fn, void *data);
void *lwt_join(lwt_t);
void lwt_die(void *);
int lwt_yeild(lwt_t);
lwt_t lwt_current(void);
int lwt_id(lwt_t);

void __lwt_schedule(void);
void __lwt_dispatch(lwt_t, lwt_t );
void __lwt_trampoline_inline(void);


int __Runqueue_add(lightweight_thread **a, lightweight_thread *b);
//int __Runqueue_remove(lwt_t);
//lwt_t __Runqueue_pop(void);
//int __Waitqueue_add(lwt_t);
//int __Waitqueue_remove(lwt_t);

#endif /* THREAD_ */
