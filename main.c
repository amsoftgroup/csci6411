#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "test.h"

int
main(int argc, char **argv)
{
	printf("main %p\n", main);
/*
	int i = 15;
	int j = 16;
	int k = 17;
	int l = 18;
	int m = 19;

	__lwt_trampoline_test(i,j,k,l,m);

	int size = -1;
	size = sizeof(lwt_t);
	printf("size of lwt_t: %i\n", size);
	size = sizeof(lightweight_thread_struct);
	printf("size of lightweight_thread_struct: %i\n", size);
*/


	void * ptr;

	int z = 0;
	void * t = NULL;
	//for (z = 0; z < 5; z++){
		lwt_fn_t callee = (void *) &__lwt_start_test0;
		void* data;
		lwt_t new_thread1 = lwt_create(callee, data);
		//lwt_t new_thread2 = lwt_create(callee, data);
		//lwt_t new_thread3 = lwt_create(callee, data);
		//lwt_t new_thread4 = lwt_create(callee, data);
		//lwt_t new_thread5 = lwt_create(callee, data);

		//lwt_t next = new_thread3->next_thread;
		//lwt_t prev = new_thread3->prev_thread;
		//ext=%i previous=%i\n", next_thread->);
		//lwt_yeild(NULL);
		//lwt_yeild(new_thread3);
		//lwt_yeild(new_thread3);
		//printf("new_thread3: %i\n", new_thread3->thread_id);
		//int id = new_thread->thread_id;
		//printf("Main new_thread: %i\n", id);
	//}



	return 1;
}


