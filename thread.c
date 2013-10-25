
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "thread.h"



volatile int max_thread_id = 0;
int sp = -1;
int ip = -1;
volatile lwt_t runqueue;
volatile lwt_t waitqueue;
volatile lwt_t current_thread;

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

		if (thread == NULL){
			printf("empty runqueue, do nothing");
			return -1;
		}else if (thread->prev_thread == NULL){
			printf("only one thread in runqueue: not yeilding: id=%i\n",thread->thread_id );
			return -1;
		}

		printf("yeilding thread id=%i\n",thread->thread_id );

		//thread->state = waiting;
		//__Runqueue_remove(thread);
		//__Waitqueue_add(thread);

		return 1;
	}

	lwt_t
	lwt_current(void)
	{
		return current_thread;
	}


	int
	lwt_id(lwt_t thread)
	{
		lightweight_thread_struct t = *thread;
		return t.thread_id;
	}

	void
	__lwt_schedule(void)
	{
		// pop the next value off the runqueue!
		lwt_t thread  = __Runqueue_pop();
		__lwt_dispatch(thread, current_thread);
	}

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{
		__Runqueue_remove(current);
		__Waitqueue_add(current);
		__Waitqueue_remove(next);
		__Runqueue_add(next);

		printf("popping: id=%i and sending %i to trampoline\n",current->thread_id, next->thread_id );
		__lwt_trampoline(next->fn, next);

		current_thread = next;

	}

	void
	__lwt_start(void)
	{
		printf("hello world");
		/* call function */
	}

	int __Runqueue_add(lwt_t thd_ptr){

		if (runqueue == NULL){
			printf("## runqueue null inserting %i\n",thd_ptr->thread_id );
			// create new runqueue: is empty
			runqueue = thd_ptr;
			printf("## runqueue is now %i\n",thd_ptr->thread_id );
		}else{
			printf("## runqueue inserting %i\n",thd_ptr->thread_id );
			//add to head
			thd_ptr->prev_thread = runqueue;
			runqueue->next_thread = thd_ptr;
			runqueue = thd_ptr;
			printf("## runqueue is now  %i\n",runqueue->thread_id );
		}
		return thd_ptr->thread_id;
	}

	lwt_t __Runqueue_pop(){

		// TODO: no need to handle NULL runqueue, we shouldn't end up here
		// learn and use assert() in C

		lwt_t ret_thread = runqueue;
		lwt_t prev_thread = runqueue->prev_thread;
		lwt_t prev_prev_thread = prev_thread->prev_thread;
		prev_thread->next_thread = NULL;
		prev_thread->prev_thread = prev_prev_thread;
		runqueue = prev_thread;
		return ret_thread;
	}


	int __Runqueue_remove(lwt_t thread){

		int found = 0;
		lwt_t prev_thread = NULL;
		lwt_t next_thread = NULL;

		while (runqueue->prev_thread != NULL){
			printf("runqueue %i\n",runqueue->thread_id );
			//printf("thread_id %i\n",thread->thread_id );

			if (runqueue->thread_id == thread->thread_id){

				printf("## thread %i = %i\n",runqueue->thread_id, thread->thread_id );

				if (thread->prev_thread != NULL){
					prev_thread = thread->prev_thread;
					prev_thread->next_thread = thread->next_thread;
				}
				if (thread->next_thread != NULL){
					next_thread = thread->next_thread;
					next_thread->prev_thread = thread->prev_thread;
				}

				//printf("## before next_thread %i\n",next_thread->thread_id );
				//printf("## before prev_thread %i\n",prev_thread->thread_id );

				//prev_thread->next_thread = next_thread;
				//next_thread->prev_thread = prev_thread;

				//printf("##next_thread %i\n",next_thread->thread_id);
				printf("##runqueue %i\n",runqueue->thread_id );
				//printf("##thread removed %i\n",thread->thread_id );
				//printf("##prev_thread %i\n",prev_thread->thread_id );
				found = 1;
			}
			if (found){
				break;
			}else{
				runqueue = runqueue->prev_thread;
			}
		}
	}

	int __Waitqueue_add(lwt_t thd_ptr){

		if (waitqueue == NULL){
			printf("## waitqueue null inserting %i\n",thd_ptr->thread_id );
			// create new waitqueue: is empty
			waitqueue = thd_ptr;
			printf("## waitqueue is now %i\n",thd_ptr->thread_id );
		}else{
			printf("## waitqueue inserting %i\n",thd_ptr->thread_id );
			//add to head
			thd_ptr->prev_thread = waitqueue;
			waitqueue->next_thread = thd_ptr;
			waitqueue = thd_ptr;
			printf("## waitqueue is now  %i\n",waitqueue->thread_id );
		}
		return thd_ptr->thread_id;
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






