/*
 * thread
 *
 *  Created on: Oct 1, 2013
 *      Author: bnr@gwu.edu
 */

#ifndef THREAD_
#define THREAD_

#define LWT_NULL = (struct thread *)0

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
	struct lightweight_thread_struct *next_thread;
	struct lightweight_thread_struct *prev_thread;
	int size;
	lwt_fn_t fn;
	void *params;
} lightweight_thread_struct;

typedef lightweight_thread_struct* lwt_t;



lwt_t lwt_create(lwt_fn_t fn, void *data);
//lwt_t lwt_create(void);
void *lwt_join(lwt_t);
void lwt_die(void *);
int lwt_yeild(lwt_t);
lwt_t lwt_current(void);
int lwt_id(lwt_t);



#endif /* THREAD_ */
