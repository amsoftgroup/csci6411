.text
.align 16
.globl __lwt_trampoline_test
__lwt_trampoline_test:

/* caller saves all registers to stack */


push %ebp
mov  %esp, %ebp
/* swap stack pointer with base pointer so we have constant, unchanging frame of reference */
//

//pushal
/* allocate 64 bytes temp memory for local vars in callee function */
//	sub $0x40, %esp

/* push parameters for our function call */

	//push 0x18(%ebp)
	//push 0x14(%ebp)
	//push 0x10(%ebp)
	//push 0x0C(%ebp)
	//push 0x08(%ebp)

/* call to C function with above parameters, demonstrating basic understanding of cdecl */
	call   *0x08(%ebp)
	//call  __lwt_start_test0 // works
	//call *(%esp) // no.
/* swap back base pointer to stack pointer */

//
/* restore our registers */
 mov %ebp, %esp
 pop %ebp

ret




