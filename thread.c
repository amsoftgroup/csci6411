
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "thread.h"
#include "test.h"

volatile int max_thread_id = 0;

volatile lwt_t *runqueue;
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
		lwt_t thd_ptr 		= (lightweight_thread *) malloc(sizeof(lightweight_thread));
		void * stack		= malloc(4096);
		thd_ptr->thread_id 	= max_thread_id++;
		thd_ptr->fn 		= fn;
		thd_ptr->state 		= ready;
		thd_ptr->params 	= data;
		thd_ptr->stack 		= stack;
		thd_ptr->sp_init 	= stack - 4096;
		thd_ptr->sp		 	= stack - 4096;
		thd_ptr->ip			=__lwt_trampoline_inline;

		printf("in lwt_create: stack=%i, %i\n", stack, thd_ptr->sp_init);


		if ((runqueue) == NULL)
		{
			printf("** __NULL");
			runqueue = (lightweight_thread**) malloc (sizeof (lightweight_thread));
			printf("** __AFTER NULL");
		}

		//(**runqueue)->thread_id = 99;
		__Runqueue_add(runqueue, thd_ptr);
		//__lwt_trampoline_inline(thd_ptr->fn, thd_ptr->params);

		//struct thd_params_t par = *(struct thd_params_t*)thd_ptr->params;
		//printf("in lwt_create: fn loc:%p thd_id=%i param_data=%i\n", fn, runqueue->thread_id, par.a);

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

		printf("** in yield threadid=%i\n", thread->thread_id);

		if (thread == NULL){
			printf("in yield with NULL parameter, pop waitqueue\n");
			__lwt_schedule();
			// pop waitqueue, add to runqueue or do nothing??????
			return -1;
		//}else if (thread->prev_thread == NULL){
		//	printf("in yield with only one thread in runqueue: not yielding: id=%i\n",thread->thread_id );
		//	return -1;
		}else{
			//printf("yielding=%i to %i\n",current_thread->thread_id , thread->thread_id);
			__lwt_dispatch(thread, runqueue);
		}

		printf("lwt_yeild to %i\n", thread->thread_id);


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
		//lightweight_thread_struct t = *thread;
		return thread->thread_id;
	}

	void
	__lwt_schedule(void)
	{
/*
		if (current_thread == NULL){
			printf(" *** __lwt_schedule: current_thread == NULL\n");
			// pop the next value off the runqueue!
			lwt_t thread  = __Runqueue_pop();
			printf(" *** __lwt_schedule: runq popped thread_id=%i\n", thread->thread_id);
			__lwt_dispatch(thread, current_thread);
		//}else if (next->state == waiting){
		}else if (current_thread->next_thread != NULL){
			printf(" *** __lwt_schedule: calling __lwt_dispatch\n");
			__lwt_dispatch(current_thread->next_thread, current_thread);
		}else{
			// next thread is not ready, move to next->next?
			// we shouldn't ever be here?
			printf("unhandled __lwt_schedule: .id=%i", current_thread->thread_id);
		}
		*/
	}

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{
		/*
		printf("__lwt_dispatch: removing %i from runqueue (%i)\n", current->thread_id, runqueue->thread_id);
		__Runqueue_remove(current);
		printf("__lwt_dispatch: runqueue = %i\n", runqueue->thread_id);
		__Waitqueue_add(current);
		__Waitqueue_remove(next);
		__Runqueue_add(next);

		printf("** __lwt_dispatch: popping id=%i and sending %i to trampoline\n",current->thread_id, next->thread_id );
		__lwt_trampoline(next->fn, next->params);

		current_thread = next;
		*/
	}

	void
	__lwt_trampoline_inline(void)
	{
		// call __lwt_start
		__asm__("call __lwt_start\n\t");
	}

	void
	__lwt_start(lwt_fn_t fn, void *data)
	{
		printf("in __lwt_start()");
	//	lwt_t t = lwt_current();
	//	lwt_die(t->fn(t->params));
	}

	int __Runqueue_add(lightweight_thread **list, lightweight_thread *thd_ptr){

		//printf("** __Runqueue_add: %i\n", th.thread_id);

		lightweight_thread *new_node = (lightweight_thread*) malloc (sizeof (lightweight_thread));

		new_node = thd_ptr;
		if (list != NULL){
			new_node->next_thread = *list;
		}

		list = new_node;


		//int t = *list->thread_id;
		printf("** __Runqueue_add: %i\n",new_node->thread_id);

		if ((runqueue) != NULL)
		{
			//printf("** __Runqueue_add: %i %i\n",new_node->thread_id, (*runqueue)->next_thread );

		}


/*
		void addFirst(struct node **list, int value){
		    struct node *new_node = (struct node*) malloc (sizeof (struct node));
		    new_node->value = value;
		    new_node->next = *list;
		    *list = new_node;
		}

*/
		return -1;
	}



