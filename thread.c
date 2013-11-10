
#include <stdlib.h>
#include <stdio.h>
#include "thread.h"
#include "test.h"

volatile int max_thread_id = 0;

volatile lwt_t *runqueue;
volatile lwt_t current_thread;

/**
 *  lwt_create: create a thread based on input, and add that thread to the runqueue.
 *  input: a function location and a pointer to the function's parameters.
 *  output: the newly created thread
 */
	lwt_t
	lwt_create(lwt_fn_t fn, void *data)
	{
		// if current_thread is null, runqueue has to be based on how we assign runqueue
		if ((current_thread) == NULL)
		{
			printf("lwt_create: Creating/adding C thread...\n");

			// there should always be at least 1 thread in the runqueue: the originating C thread
			//  if we're here, we need to add the originating C thread to the runqueue.

			printf("lwt_create: runqueue is NULL. Adding C thread.\n");

			lwt_t c_thread = (lightweight_thread *) malloc(sizeof(lightweight_thread));
			unsigned int *stack_ptr	= malloc(4096);//unsigned int
			c_thread->thread_id = 0; // zero will uniquely define the initial C thread.. the parent of all possible threads
			c_thread->state		= running;
			c_thread->sp_init 	= stack_ptr;
			c_thread->sp		= stack_ptr + 4096/sizeof(unsigned int); //or &stack_ptr[4096/sizeof(unsigned int)]
			c_thread->ip		= __lwt_trampoline_inline;
			runqueue = (lightweight_thread**) malloc (sizeof (lightweight_thread));
			*runqueue =  c_thread;
			printf("lwt_create __AFTER NULL\n");
			current_thread = *runqueue;
		}

		// Finally, create and add the new thread assuming current_thread and runqueue exist

		lwt_t thd_ptr 			= (lightweight_thread *) malloc(sizeof(lightweight_thread));
		unsigned int *stack_ptr	= malloc(4096);//unsigned int
		thd_ptr->thread_id 		= max_thread_id++;
		thd_ptr->fn 			= fn;
		thd_ptr->state 			= ready;
		thd_ptr->params 		= data;
		thd_ptr->sp_init 		= stack_ptr;
		thd_ptr->sp		 		= stack_ptr + 4096/sizeof(unsigned int); //or &stack_ptr[4096/sizeof(unsigned int)]
		thd_ptr->ip				= __lwt_trampoline_inline;

		printf("lwt_create: stack=%p, (%i) id = %i\n", thd_ptr->sp, thd_ptr->sp, thd_ptr->thread_id);

		unsigned int j = __Runqueue_add(runqueue, thd_ptr);

		printf("lwt_create: leaving after adding %i (thd_ptr=%i)\n", j, thd_ptr->thread_id);

		return thd_ptr;
	}

	void *
	lwt_join(lwt_t thread)
	{
		// get all child threads of thread
		// while (child thread->state != done){
			//wait
		//}
		// return parent_thread->retval;
	}

	void
	lwt_die(void *ptr)
	{
		//Runqueue_pop(runqueue);
//		current_thread->

	}

	unsigned int
	lwt_yield(lwt_t thread){

		if (thread){
			printf("lwt_yield: runqueue(%i) yielding to (%i)\n", (current_thread)->thread_id, thread->thread_id);
			if (runqueue){
				printf("lwt_yield: !runqueue calling dispatch thread_TCB=%p, current_thread_TCB = %p\n", thread->sp, (*runqueue)->sp);
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

	unsigned int
	lwt_id(lwt_t thread)
	{
		lwt_t t = thread;
		return t->thread_id;
	}

	void
	__lwt_schedule(void)
	{
		lightweight_thread *thread = __Runqueue_pop(runqueue);
		printf("__lwt_schedule: popped %i\n", thread->thread_id);
		printf("__lwt_schedule: thread TCB address %i (%p)\n", thread->sp, thread->sp);

		if (current_thread){
			printf("__lwt_schedule: calling __lwt_dispatch, thread %i current_thread %i\n", thread->thread_id, current_thread->thread_id);
			printf("	thread SP=		%i\n", thread->sp);
			printf("	current_thread SP=	%i\n", current_thread->sp);
			__lwt_dispatch(thread, current_thread);
			current_thread = thread;
		}else{
			printf("__lwt_schedule: no thds exe skipping\n");
		}
	}

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{
		//printf("__lwt_dispatch: next %f\n",(double)next->stack);
		printf("__lwt_dispatch: before current_thread %i\n",(unsigned int)current_thread->thread_id);

		if (current){
			printf("__lwt_dispatch: calling dipatch.S, current thread id is %i, next %i\n", current->thread_id, next->thread_id);
			printf("__lwt_dispatch: calling dipatch.S, current TCB is %i, next %i\n", current->sp, next->sp);

			//printf("__lwt_dispatch after pushal");
			printf("__lwt_dispatch:\n	next.SP=	%i\n	next.IP=	%i\n	current.SP=	%i\n	current.IP=	%i\n", next->sp, next->ip, current->sp, current->ip);
			//__asm__("pushal\n\t");
			//__lwt_start_test4(next->sp, next->ip, current->sp, current->ip);
			dispatcher(next->sp, next->ip, current->sp, current->ip);
			//__asm__("popal\n\t");

		}else{
			printf("__lwt_dispatch: no thread executing. skipping dispatch.\n");
		}

		// TODO: figure this one out.
		current_thread = next;
		//current_thread->thread_id = next->thread_id;
		printf("__lwt_dispatch: after current_thread %i\n",current_thread->thread_id);
	}

	void
	__lwt_trampoline_inline()
	{
		// call __lwt_start
		printf ("__lwt_trampoline_inline: calling __lwt_start\n");
		__asm__("call __lwt_start\n\t");
	}

/*
	int
	__lwt_start(void)
	{
		printf("__lwt_start: in __lwt_start()");
		return 1;
	}
*/

	void
	__lwt_start(lwt_fn_t fn, void *data)
	{
		printf("in __lwt_start()");
		lwt_t t = lwt_current();
		lwt_die(t->fn(t->params));

	}

	unsigned int
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
		new_node->state = thd_ptr->state;

		*list = new_node;

		printf("__Runqueue_add: after,__Runqueue_size = %i\n", __Runqueue_size(*list));
		if (current_thread){
			printf("__Runqueue_add: after,current_thread = %i\n",current_thread->thread_id);
		}

		printf("__Runqueue_add: after, *list = %i\n",(*list)->thread_id);

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
