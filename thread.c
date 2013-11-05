
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "thread.h"
#include "test.h"

volatile int max_thread_id = 0;

volatile lwt_t *runqueue;
//volatile lwt_t waitqueue;
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
		void *stack_ptr	= malloc(4096);
		//printf("lwt_create: malloc %p\n", stack);
		//double *stack 		= (double *) stack_ptr;
		thd_ptr->thread_id 	= max_thread_id++;
		thd_ptr->fn 		= fn;
		thd_ptr->state 		= ready;
		thd_ptr->params 	= data;
		thd_ptr->stack 		= stack_ptr;
		thd_ptr->sp_init 	= stack_ptr;
		thd_ptr->sp		 	= stack_ptr;
		thd_ptr->ip			= __lwt_trampoline_inline;
		//void * fp_ptr 		= __lwt_trampoline_inline;
		//thd_ptr->ip			= (double) *fp_ptr;

		printf("in lwt_create: stack=%p, %i\n", stack_ptr, thd_ptr->sp_init);

		if ((runqueue) == NULL)
		{
			printf("lwt_create: runqueue is NULL\n");
			runqueue = (lightweight_thread**) malloc (sizeof (lightweight_thread));
			printf("lwt_create __AFTER NULL\n");
			current_thread = thd_ptr;
		}

		__Runqueue_add(runqueue, thd_ptr);

		return thd_ptr;
	}

	void *
	lwt_join(lwt_t thread)
	{
		while (thread->state != done){

		}
		return thread->retval;
	}

	void
	lwt_die(void *)
	{
		current_thread->

	}

	double
	lwt_yield(lwt_t thread){

		if (thread){
			printf("lwt_yield: runqueue(%i) yielding to (%i)\n", (current_thread)->thread_id, thread->thread_id);
			if (runqueue){
				printf("lwt_yield: !runqueue calling dispatch thread_TCB=%p, current_thread_TCB = %p\n", thread->stack, (*runqueue)->stack);
				__lwt_dispatch(thread, *runqueue);
			}
		}else{
			printf("lwt_yield: in yield with NULL parameter\n");
			__lwt_schedule();
		}
		return -1;
	}

	lwt_t
	lwt_current(void)
	{
		return current_thread;
	}

	double
	lwt_id(lwt_t thread)
	{
		//lightweight_thread_struct t = *thread;
		return thread->thread_id;
	}

	void
	__lwt_schedule(void)
	{
		lightweight_thread *thread = __Runqueue_pop(runqueue);
		printf("__lwt_schedule: popped %i\n", thread->thread_id);
		printf("__lwt_schedule: thread TCB address %i (%p)\n", thread->stack, thread->stack);
		//printf("__lwt_schedule: runqueue %i\n", (*runqueue)->thread_id);
		//printf("__lwt_schedule: current_thread %i\n", (current_thread)->thread_id);

		if (current_thread){
			printf("__lwt_schedule: calling __lwt_schedule, current is %i\n", current_thread->thread_id);
			__lwt_dispatch(thread, current_thread);
			current_thread = thread;
		}else{
			printf("__lwt_schedule: no thds exe skipping\n");
			//current_thread = thread;
		}
	}

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{
		//printf("__lwt_dispatch: next %f\n",(double)next->stack);
		printf("__lwt_dispatch: before current_thread %i\n",(double)current_thread->thread_id);


		if (current){
			printf("__lwt_dispatch: calling dipatch.S, current thread id is %i, next %i\n", current->thread_id, next->thread_id);
			printf("__lwt_dispatch: calling dipatch.S, current TCB is %p, next %p\n", current->stack, next->stack);
			dispatcher(next->stack, current->stack);
		}else{
			printf("__lwt_dispatch: no thread executing. skipping dispatch.\n");
		}

		current_thread = next;
		printf("__lwt_dispatch: after current_thread %i\n",(double)current_thread->thread_id);
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
		lwt_t t = lwt_current();
		lwt_die(t->fn(t->params));
	}

	double
	__Runqueue_add(lightweight_thread **list, lightweight_thread *thd_ptr){

		printf("__Runqueue_add: before __Runqueue_size = %i\n", __Runqueue_size(*list));

		if (!list){

			printf("__Runqueue_add: priming current_thread var. setting current thread to %i\n", (thd_ptr)->thread_id);
			//current_thread = (lightweight_thread*) malloc (sizeof (lightweight_thread));
			current_thread = *list;
		}

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

		printf("__Runqueue_add: after,__Runqueue_size = %i\n", __Runqueue_size(*list));
		if (current_thread){
			printf("__Runqueue_add: after,current_thread = %i\n",current_thread->thread_id);
		}
		return (*list)->thread_id;
	}

	lightweight_thread*
	__Runqueue_pop(lightweight_thread **Head)
	{
		printf("__Runqueue_pop: before __Runqueue_size = %i\n", __Runqueue_size(*Head));
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
		 printf("__Runqueue_pop: after __Runqueue_size = %i\n", __Runqueue_size(*Head));
		// printf("** __Runqueue_pop popping %i\n", temp->thread_id);
		 return temp;
	}

	int __Runqueue_size(lightweight_thread *item)
	{
	  lightweight_thread* cur = item;
	  int size = 0;

	  while (cur != NULL)
	  {
	    ++size;
	    cur = cur->next_thread;
	  }

	  return size;
	}
