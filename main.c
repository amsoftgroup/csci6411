#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "test.h"

int
main(int argc, char **argv)
{

		struct thd_params_t *args = malloc(sizeof(struct thd_params_t));

		args->a = 0;
		args->b = 0;
		printf("MAIN calling lwt_create(__lwt_start_test0, args);\n");
		lwt_t new_thread_0 = lwt_create(__lwt_call_test0, args);
		printf("MAIN returning from lwt_create(__lwt_start_test0, args);\n");

		args->a = 1;
		args->b = 1;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_1 = lwt_create(__lwt_call_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");

		printf("MAIN calling lwt_yield(LWT_NULL);\n");
		lwt_yield(LWT_NULL);
		printf("MAIN returning from lwt_yield(LWT_NULL);\n");


	return 0;
}


