
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "thread.h"



volatile int max_thread_id = 0;
int sp = -1;
int ip = -1;
lwt_t runqueue;
lwt_t waitqueue_next;

/**
 *  lwt_create: create a thread based on input, and add that thread to the runqueue.
 *  input: a function location and a pointer to the function's parameters.
 *  output: the newly created thread
 */
lwt_t
lwt_create(lwt_fn_t fn, void *data)
{
	lwt_t thd_ptr = (lightweight_thread_struct *) malloc(sizeof(lightweight_thread_struct));

	thd_ptr->thread_id = max_thread_id++;
	thd_ptr->fn = fn;
	thd_ptr->state = ready;

	/**
	 * add thread to runqueue
	 */
	if (runqueue == NULL){
		// create new runqueue: is empty
		runqueue = thd_ptr;
		runqueue->prev_thread = NULL;
		runqueue->next_thread = NULL;
	}else{
		//add to head
		runqueue->next_thread = NULL;
		thd_ptr->prev_thread = runqueue;
		runqueue = thd_ptr;
	}

	//runq[thd_ptr->thread_id] = thd_ptr;
	printf("in lwt_create: %p %i\n", fn, runqueue->thread_id);
	return thd_ptr;
}

void
*lwt_join(lwt_t thread)
{

	// free the stack of the dieing thread here
}

void
lwt_die(void * thread)
{

}


int lwt_yeild(lwt_t thread){

	/** remove thread from runqueue
	 * reassign next thread to point to previous,
	 * and previous to point to the next.
	 */
	printf("yeilding thread id=%i\n",thread->thread_id );

	//printf("runqueue->next_thread %i\n", );
	thread->state = waiting;
	while (runqueue->next_thread != NULL){
		printf("runqueue %i\n",runqueue->thread_id );
		if (runqueue->thread_id == thread->thread_id){
			lwt_t prev_thread = thread->prev_thread;
			lwt_t next_thread = thread->next_thread;
			prev_thread->next_thread = next_thread;
			next_thread->prev_thread = prev_thread;

			printf("FOUND thread %i\n",runqueue->thread_id );
			break;
		}
		runqueue = runqueue->next_thread;

	}

	//place on waitqueue with
}

lwt_t
lwt_current(void)
{
	return NULL;
}


int
lwt_id(lwt_t thread)
{

	//lightweight_thread_struct t = *thread;
	// return t.thread_id;

	return NULL;

}

void
__lwt_schedule(void)
{

}


void
__lwt_dispatch(lwt_t next, lwt_t current)
{

}


void
__lwt_start(void)
{
	printf("hello world");
	/* call function */
}






