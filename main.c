#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "test.h"

int
main(int argc, char **argv)
{
	void * ptr;
	int z = 0;
	void * t = NULL;
	for (z = 0; z < 5; z++){
		//lwt_fn_t callee = (void *) &__lwt_start_test0;
		void* data;
		lwt_t new_thread_0 = lwt_create(__lwt_start_test0, data);
		lwt_t new_thread_1 = lwt_create(__lwt_start_test0, data);
		lwt_t new_thread_2 = lwt_create(__lwt_start_test0, data);
		lwt_t new_thread_3 = lwt_create(__lwt_start_test0, data);
		lwt_t new_thread_4 = lwt_create(__lwt_start_test0, data);
		//lwt_yeild(NULL); // seg fault
		lwt_yeild(new_thread_2);
		__lwt_schedule();
	}
	return 1;
}


