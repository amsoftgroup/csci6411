
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "thread.h"



volatile int max_thread_id = 0;
int sp = -1;
int ip = -1;
volatile lwt_t runqueue;
volatile lwt_t waitqueue;

/**
 *  lwt_create: create a thread based on input, and add that thread to the runqueue.
 *  input: a function location and a pointer to the function's parameters.
 *  output: the newly created thread
 */
lwt_t
lwt_create(lwt_fn_t fn, void *data)
{
	lwt_t thd_ptr = (lightweight_thread_struct *) malloc(sizeof(lightweight_thread_struct));
	printf("fn %p\n", fn);

	__lwt_trampoline(fn, (void *)thd_ptr);

	thd_ptr->thread_id = max_thread_id++;
	thd_ptr->fn = fn;
	thd_ptr->state = ready;
	__Runqueue_add(thd_ptr);
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

int
lwt_yeild(lwt_t thread){

	/*** remove thread from runqueue, add to waitqueue
	 * reassign next thread to point to previous,
	 * and previous to point to the next.
	 */
	printf("yeilding thread id=%i\n",thread->thread_id );

	if (thread == NULL){
		// special case:
	}

	thread->state = waiting;
	__Runqueue_remove(thread);
	__Waitqueue_add(thread);

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

	return -1;

}

void
__lwt_schedule(void)
{
	// pop the next value off the runqueue!
	lwt_t thread  = __Runqueue_pop();


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

	int __Runqueue_add(lwt_t thd_ptr){
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
			runqueue->next_thread = thd_ptr;
			thd_ptr->prev_thread = runqueue;
			runqueue = thd_ptr;
		}
		return 1;
	}

	lwt_t __Runqueue_pop(void){

		// TODO: no need to handle NULL runqueue, we shouldn't end up here
		// learn and use assert() in C

		lwt_t ret_thread = runqueue;
		lwt_t prev_thread = runqueue->prev_thread;
		prev_thread->next_thread = NULL;
		runqueue = prev_thread;
		return ret_thread;
	}


	int __Runqueue_remove(lwt_t thread){

		while (runqueue->prev_thread != NULL){
			printf("runqueue %i\n",runqueue->thread_id );
			printf("thread_id %i\n",thread->thread_id );

			if (runqueue->thread_id == thread->thread_id){

				lwt_t prev_thread = runqueue->prev_thread;
				printf("##prev_thread %i\n",prev_thread->thread_id );
				lwt_t next_thread = runqueue->next_thread;
				printf("##next_thread %i\n",next_thread->thread_id );
				prev_thread->next_thread = runqueue->next_thread;
				next_thread->prev_thread = runqueue->prev_thread;
				printf("FOUND thread %i\n",runqueue->thread_id );

			}
			runqueue = runqueue->prev_thread;
		}
	}

	int __Waitqueue_add(lwt_t thd_ptr){

		if (waitqueue == NULL){
			// create new runqueue: is empty
			waitqueue = thd_ptr;
			waitqueue->prev_thread = NULL;
			waitqueue->next_thread = NULL;
		}else{
			//add to head
			waitqueue->next_thread = thd_ptr;
			thd_ptr->prev_thread = waitqueue;
			waitqueue = thd_ptr;

		}
		return 1;
	}

	int __Waitqueue_remove(lwt_t thread){

		while (waitqueue->prev_thread != NULL){
			printf("runqueue %i\n",waitqueue->thread_id );
			printf("thread_id %i\n",thread->thread_id );
			if (waitqueue->thread_id == thread->thread_id){

				lwt_t prev_thread = waitqueue->prev_thread;
				printf("##prev_thread %i\n",prev_thread->thread_id );
				lwt_t next_thread = waitqueue->next_thread;
				printf("##next_thread %i\n",next_thread->thread_id );
				prev_thread->next_thread = waitqueue->next_thread;
				next_thread->prev_thread = waitqueue->prev_thread;
				printf("FOUND thread %i\n",waitqueue->thread_id );

			}
			waitqueue = waitqueue->prev_thread;
		}

		return 1;

}




