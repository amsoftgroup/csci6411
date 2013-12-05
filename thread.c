
#include <stdlib.h>
#include <stdio.h>
#include "thread.h"
#include "test.h"

volatile int max_thread_id = 1;

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
		void tramp_testing(void);

		// if current_thread is null, we haven't added the main C thread
		if ((current_thread) == NULL)
		{
			// there should always be at least 1 thread in the runqueue: the originating C thread
			//  if we're here, we need to add the originating C thread to the runqueue.

			printf("lwt_create: runqueue is NULL. Adding C thread.\n");

			lwt_t c_thread = (lightweight_thread *) malloc(sizeof(lightweight_thread));
			unsigned int *stack_ptr	= malloc(4096);//unsigned int
			c_thread->thread_id = 0; // zero will uniquely define the initial C thread.. the parent of all possible threads
			c_thread->state		= running;
			c_thread->sp_init 	= stack_ptr;
			//c_thread->sp		= stack_ptr + 4096/sizeof(unsigned int); //or &stack_ptr[4096/sizeof(unsigned int)]
			c_thread->sp		= stack_ptr + (4096-sizeof(unsigned int))/sizeof(unsigned int);
			c_thread->ip		= tramp_testing;
			//c_thread->fn		= ?;
			//c_thread->params	= ?;
			runqueue = (lwt_t*) malloc (sizeof (lightweight_thread));
			*runqueue =  c_thread;

			current_thread = *runqueue;

			printf("#### lwt_create: C thread is current_thread=%i\n", current_thread->thread_id);
		}

		// Finally, create and add the new thread assuming current_thread and runqueue exist
		int tramp_testing_params(void *ptr);

		lwt_t thd_ptr 			= (lightweight_thread *) malloc(sizeof(lightweight_thread));
		unsigned int *stack_ptr	= malloc(4096);//unsigned int
		thd_ptr->thread_id 		= max_thread_id++;
		thd_ptr->fn 			= fn;
		thd_ptr->state 			= ready;
		thd_ptr->params 		= data;
		thd_ptr->sp_init 		= stack_ptr;
		thd_ptr->sp		 		= stack_ptr + (4096-sizeof(unsigned int))/sizeof(unsigned int); //or &stack_ptr[4096/sizeof(unsigned int)]
		thd_ptr->ip				= tramp_testing_params(data);

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
		//current_thread->

	}

	unsigned int
	lwt_yield(lwt_t thread){

		if (thread){
			printf("lwt_yield: current_thread(%i) yielding to (%i)\n", (current_thread)->thread_id, thread->thread_id);
			if (runqueue){
				printf("lwt_yield: !runqueue calling dispatch thread_TCB=%p, current_thread_TCB = %p\n", thread->sp, (*runqueue)->sp);
				__lwt_dispatch(thread, current_thread);
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
		return thread->thread_id;
	}

	void
	__lwt_schedule(void)
	{
		printf("__lwt_schedule: \n");
		lightweight_thread *thread = __Runqueue_pop(runqueue);
		printf("__lwt_schedule: thread TCB address %i (%p)\n", thread->sp, thread->sp);

		if (thread){
			printf("__lwt_schedule: calling __lwt_dispatch, thread %i current_thread %i\n", thread->thread_id, current_thread->thread_id);
			printf("	thread SP=		%p\n", thread->sp);
			printf("	current_thread SP=	%p\n", current_thread->sp);
			__lwt_dispatch(thread, current_thread);
		}else{
			printf("__lwt_schedule: no thds exe skipping\n");
		}
	}

	volatile lwt_t savedcur, savednext;

	void
	__lwt_dispatch(lwt_t next, lwt_t current)
	{

		printf("__lwt_dispatch: \n");// current_thread %i\n",current_thread->thread_id);

		savedcur = current;
		savednext = next;

		if (current){

			printf("__lwt_dispatch (before):\n	next.SP=	%p\n	next.IP=	%p\n	current.SP=	%p\n	current.IP=	%p\n", next->sp, next->ip, current->sp, current->ip);
			unsigned int *ptr_sp = &(current->sp);
			unsigned int *ptr_ip = &(current->ip);
			dispatcher(next->sp, next->ip, ptr_sp, ptr_ip);
			printf("__lwt_dispatch (after):\n	next.SP=	%p\n	next.IP=	%p\n	current.SP=	%p\n	current.IP=	%p\n", next->sp, next->ip, current->sp, current->ip);
		}else{
			printf("__lwt_dispatch: no thread executing. skipping dispatch.\n");
		}

		current_thread = next;

		printf("#### __lwt_dispatch: current_thread is now %i\n", current_thread->thread_id);

	}

	void
	__lwt_start(void) /* lwt_fn_t fn, void *data */
	{
		//__lwt_dispatch(savedcur, savednext);
		//__lwt_start_test0();
		//__asm__("push \n\t");
		//__asm__("call __lwt_call_test1\n\t");

		(current_thread)->fn;//((current_thread)->params);
		printf("__lwt_start(): entered\n");

		//int (*func)(int) = (int (*)(void))current_thread->fn;
		//int x = func(current_thread->params);

		//int (*func)(void) = (int (*)(void)) current_thread->fn;
		//int x = func();
		//t(1);
		//

		//lwt_t t = lwt_current();
		//lwt_die(t->fn(t->params));

	}

	unsigned int
	__Runqueue_add(lightweight_thread **list, lightweight_thread *thd_ptr){

		printf("__Runqueue_add: before __Runqueue_size = %i\n", __Runqueue_size(*list));


		if (!list){

			printf("__Runqueue_add: priming current_thread var. setting current thread to %i\n", (thd_ptr)->thread_id);
			//current_thread = (lightweight_thread*) malloc (sizeof (lightweight_thread));
			current_thread = *list;
			printf("#### __Runqueue_add: !list: current_thread is now %i\n", current_thread->thread_id);
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
		printf("__Runqueue_pop: before Head %i  \n", (*Head)->thread_id);
		lightweight_thread *temp = *Head;
		 if (temp) {
			 if (temp->next_thread){
				 *Head = temp->next_thread;
			 }
		 }else{
			 printf("__Runqueue_pop: Head NULL");

		 }
		 printf("__Runqueue_pop: after Head %i __Runqueue_size = %i\n",  (*Head)->thread_id, __Runqueue_size(*Head));
		 printf("** __Runqueue_pop returning %i\n", temp->thread_id);
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
