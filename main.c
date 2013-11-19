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

		args->a = 0;
		args->b = 0;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_0 = lwt_create(__lwt_start_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");

		args->a = 1;
		args->b = 1;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_1 = lwt_create(__lwt_start_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");

		printf("MAIN calling lwt_yield(LWT_NULL);\n");
		lwt_yield(LWT_NULL);
		printf("MAIN returning from lwt_yield(LWT_NULL);\n");


/*
		args->a = 2;
		args->b = 2;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_2 = lwt_create(__lwt_start_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");
		//printf("MAIN calling lwt_yield(new_thread_1)");
		//lwt_yield(new_thread_1);

		args->a = 3;
		args->b = 3;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_3 = lwt_create(__lwt_start_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");

		printf("MAIN calling lwt_yield(new_thread_2);\n");
		lwt_yield(new_thread_2);
		printf("MAIN returning from lwt_yield(new_thread_2);\n");

		args->a = 4;
		args->b = 4;
		printf("MAIN calling lwt_create(__lwt_start_test1, args);\n");
		lwt_t new_thread_4 = lwt_create(__lwt_start_test1, args);
		printf("MAIN returning from lwt_create(__lwt_start_test1, args);\n");
		//lwt_yield(new_thread_1);
	//);
*/
	return 0;
}


