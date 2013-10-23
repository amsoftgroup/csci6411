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
		lwt_t new_thread = lwt_create(__lwt_start_test0, data);
		//lwt_yeild(NULL);
		//lwt_yeild(new_thread3);
	}
	return 1;
}


