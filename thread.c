/*
 * thread.c
 *
 *  Created on: Oct 4, 2013
 *      Author: cos
 */
lwt_t current_thread;

lwt_t lwt_create(lwt_fn_t fn, void *data){

}
void *lwt_join(lwt_t){

}
void lwt_die(void *){

}
int lwt_yeild(lwt_t thread){

}
lwt_t lwt_current(void){
	return current_thread;
}
int lwt_id(lwt_t thread){
	 return thread.thread_id;
}

void __lwt_schedule(void){

}

void __lwt_dispatch(lwt_t next, lwt_t current){

}

__lwt_trampoline(){
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

__lwt_start(){
	/* call function */
}




