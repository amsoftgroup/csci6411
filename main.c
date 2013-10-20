#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "test.h"


int
main(int argc, char **argv)
{
	int i = 15;
	int j = 16;
	int k = 17;
	int l = 18;
	int m = 19;

	__lwt_trampoline(i,j,k,l,m);

	int size = sizeof(int);
	printf("size of int: %i\n", size);

	size = sizeof(lwt_t);
	printf("size of lwt_t: %i\n", size);
	printf("size of lightweight_thread_struct: %i\n", size);

	void * ptr;

	int z = 0;
	void * t = NULL;
	//for (z = 0; z < 5; z++){
		lwt_fn_t callee = (void *) &__lwt_start_test5;
		lwt_t new_thread1 = lwt_create(callee, 1);
		lwt_t new_thread2 = lwt_create(callee, 2);
		lwt_t new_thread3 = lwt_create(callee, 3);
		lwt_t new_thread4 = lwt_create(callee, 4);
		lwt_t new_thread5 = lwt_create(callee, 5);
		lwt_yeild(new_thread3);
		//int id = new_thread->thread_id;
		//printf("Main new_thread: %i\n", id);
	//}

	printf("main %p\n", main);


/*
 * 1) Use the lwt_trampoline_test to call a function you implement called
lwt_start. You must understand cdecl to be able to think about this. See the resources.

	asm(
		".align 16\n\t"
		".globl\n\t"
		"__lwt_trampoline_test:\n\t"
			"call lwt_start\n\t"

	);
*/

/* 	2) Change that function so that you can pass a single argument to the lwt start.
using objdump:
int i = test3(22,33,44);
   9:	c7 44 24 08 2c 00 00 	movl   $0x2c,0x8(%esp)
  10:	00
  11:	c7 44 24 04 21 00 00 	movl   $0x21,0x4(%esp)
  18:	00
  19:	c7 04 24 16 00 00 00 	movl   $0x16,(%esp)
  20:	e8 fc ff ff ff       	call   21 <main+0x21>
  25:	89 44 24 1c          	mov    %eax,0x1c(%esp)

	asm(
			".align 16\n\t"
			".globl\n\t"
			"push   $0x4\n\t"
			"push   $0x3\n\t"
			"push   $0x2\n\t"
			"call   __lwt_start_test\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
	);
	 */


/*
 *
 * 3) Write a simple inline assembly function that includes a simple forward jump to a label (maybe jumping
	over some garbage instructions), and continues executing in the C function.

	asm(
		".align 16\n\t"
		".globl\n\t"
		"__lwt_trampoline_test:\n\t"
			"push   $0x4\n\t"
			"push   $0x3\n\t"
			"push   $0x2\n\t"
			"jmp label1\n\t"
			"movl $0, %eax\n\t"
			"movl (%eax), %ebx\n\t"
		"label1:\n\t"
			"call __lwt_start_test\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
	);
 */
/* 4) Write an inline assembly function that trashes the eax register (e.g. by doing movl $DEADBEEF,
%eax) and correspondingly adds the eax register to the clobber list.

      // asm ( assembler template
      //     : output operands                  // optional
      //     : input operands                   // optional
      //     : list of clobbered registers      // optional
      //     );


	asm(
			"movl $0xDEADBEEF, (%%eax)\n\t"
			"call lwt_start\n\t"
			: //no input
			: // no output
			  :"%eax"
	);
 */
/* 5) Write a version of your inline assembly function for dispatching between threads that simply saves all
registers of the current thread, and restores the registers also of the current thread. Check out the
objdump output of your program and confirm it makes sense. Your program should execute as normal
when calling this function (i.e. it should have no impact).
// temp . ESP
 //                        PUSH   EAX
 //                        PUSH   ECX
 //                        PUSH   EDX
 //                        PUSH   EBX
 //                        PUSH   temp
 //                        PUSH   EBP
 //                        PUSH   ESI
 //                        PUSH   EDI


	asm(
			"movl $0x5, %eax\n\t"
			"movl $0x6, %ecx\n\t"
			"movl $0x7, %edx\n\t"
			"pushal\n\t"
			"push   %eax\n\t"
			"push   %ecx\n\t"
			"push   %edx\n\t"
			"call   __lwt_start_test3\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"popal\n\t"

	);
	 */

	/* 6) Now implement your actual dispatch function. The inputs into the inline assembly should be two
locations in the current thread’s TCB that you can use in the assembly to save the instruction and
stack pointers, and two values that correspond to the instruction and stack pointers of the thread you
want to switch to. The inline assembly should expand on your previous version by saving and restoring
these values appropriately. At this point you should have successfully implemented your dispatch function.
You have to do one last thing before you can test it.


	asm(
			"movl $0x5, %eax\n\t"
			"movl $0x6, %ecx\n\t"
			"movl $0x7, %edx\n\t"
			"pusha\n\t"
			"push   %eax\n\t"
			"push   %ecx\n\t"
			"push   %edx\n\t"
			"call   __lwt_start_test\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"pop (%esp)\n\t"
			"popa\n\t"
	);

	 */
/*
int test(int i){
	i = i + 1;
	//return i;
	return test2(i,7,8);
}

int  test2(int i, int j, int k){
	i = i + 1;
	j = j + 2;
	k = k + 3;
	return test3(i,j,k);
}

int test3(int i, int j, int k){
	return i + j + k;

}
*/
	return 1;
}


