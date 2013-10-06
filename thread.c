
#include "thread.h";


lwt_t current_thread;

lwt_t lwt_create(lwt_fn_t fn, void *data){

}

void *lwt_join(lwt_t thread){

}

void lwt_die(void * thread){

}

int lwt_yeild(lwt_t thread){

}

lwt_t lwt_current(void){
	return current_thread;
}

int lwt_id(lwt_t thread){

	lightweight_thread_struct t = *thread;
	 return t.thread_id;

}

void __lwt_schedule(void){

}

void __lwt_dispatch(lwt_t next, lwt_t current){

}

void __lwt_trampoline(void){
	asm(
			/* CALL __lwt_start() */
			"movl $0x5, %eax\n\t"
			"movl $0x6, %ecx\n\t"
			"movl $0x7, %edx\n\t"
			"pusha\n\t"
			"push   %eax\n\t"
			"push   %ecx\n\t"
			"push   %edx\n\t"
			"call   __lwt_start\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"popa\n\t"
	);
}

void __lwt_start(void){
	printf("hello world");
	/* call function */
}




