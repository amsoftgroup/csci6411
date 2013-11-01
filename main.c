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
	//for (z = 0; z < 5; z++){

		struct thd_params_t *args = malloc(sizeof(struct thd_params_t));
		args->a = 42;
		args->b = 0xDEADBEEF;

		lwt_t new_thread_0 = lwt_create(__lwt_start_test1, args);
		lwt_yeild(LWT_NULL);
		lwt_t new_thread_1 = lwt_create(__lwt_start_test1, args);
		lwt_yeild(LWT_NULL);
		lwt_yeild(LWT_NULL);
		lwt_yeild(LWT_NULL);
		lwt_t new_thread_2 = lwt_create(__lwt_start_test1, args);
		lwt_t new_thread_3 = lwt_create(__lwt_start_test1, args);
		lwt_t new_thread_4 = lwt_create(__lwt_start_test1, args);
		lwt_yeild(LWT_NULL);
		//lwt_yeild(LWT_NULL);
		lwt_yeild(new_thread_1);
	//);

	return 0;
}


