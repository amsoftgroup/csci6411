
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
		//printf("****** before rq: %i\n", (**runqueue));
		__Runqueue_add(runqueue, thd_ptr);
		//printf("****** AFTER rq: %i\n", (**runqueue));
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

		if (thread){
			printf("runqueue(%i) yielding to %i\n", (*runqueue)->thread_id, thread->thread_id);
			if (!*runqueue){
				__lwt_dispatch(thread, *runqueue);
			}
		}else{
			printf("in yield with NULL parameter\n");
			__lwt_schedule();
		}
		return -1;
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
		//int before = (*runqueue)->thread_id;
		printf("__lwt_schedule: runqueue %i\n", (*runqueue)->thread_id);
		lightweight_thread *thread = __Runqueue_pop(runqueue);
		//int after = (*runqueue)->thread_id;
		//printf("__lwt_schedule: popped %i\n", thread->thread_id);
		printf("__lwt_schedule: runqueue %i\n", (*runqueue)->thread_id);

		//__lwt_dispatch(thread, current_thread);

/*
		if (before != after){
			__lwt_dispatch(thread, current_thread);
		}else{
			printf("__lwt_schedule: runqueue did not change, no call to dispatch");
		}
*/
	}

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{
		printf("__lwt_dispatch\n");
		dispatcher(next->stack, current->stack);
		//current_thread = next;
		//printf("__lwt_dispatch: next %i, current %i\n", next->thread_id ,current->thread_id );
		// Call context switching __dispatch.S (see notes)

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

	int
	__Runqueue_add(lightweight_thread **list, lightweight_thread *thd_ptr){

		lightweight_thread *new_node = (lightweight_thread*) malloc (sizeof (lightweight_thread));
		new_node = thd_ptr;
		new_node->thread_id = thd_ptr->thread_id;
		new_node->fn = thd_ptr->fn;
		new_node->ip = thd_ptr->ip;
		new_node->next_thread = *list;
		new_node->params = thd_ptr->params;
		new_node->parent_id = thd_ptr->parent_id;
		new_node->size = thd_ptr->size; // //TODO: needed????
		new_node->sp = thd_ptr->sp;
		new_node->sp_init = thd_ptr->sp_init;
		new_node->stack = thd_ptr->stack;
		new_node->state = thd_ptr->state;

		*list = new_node;

		return (*list)->thread_id;
	}

	lightweight_thread*
	__Runqueue_pop(lightweight_thread **Head)
	{
		lightweight_thread *temp = *Head;
		 if (temp) {
			 printf(": Head %i  \n", (*Head)->thread_id);
			 if (temp->next_thread){
				 *Head = temp->next_thread;
			 }
			 printf("__Runqueue_pop: Head %i  \n", (*Head)->thread_id);
		 }else{
			 printf("__Runqueue_pop: Head NULL");

		 }
		// printf("** __Runqueue_pop popping %i\n", temp->thread_id);
		 return temp;
	}

/*
 *
 * Node *pop(Node **AddressOfHead) {
    Node *temp = *AddressOfHead;
    if (temp) {
        *AddressOfHead = temp->next;
    }
    return temp;
}

...

// Usage example
Node *TopOfList = pop(&Head);

 */
