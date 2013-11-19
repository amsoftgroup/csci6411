.text
.align 16
.globl dispatcher
dispatcher:

/*
- formula for doing all of this:
- you need the sp and the ip you want to switch to (can pass as arguments)
- you need the **address** of the sp and ip you are switching away from so that
- you can save those to the proper locations within the assembly, you are
- worried about 1) reading and writing those values, which you can test by
- making this function "normal" (no switching), and 2) saving and restoring
- the "proper" values.

- you can add saving and restoring logic for normal registers before adding
- switching At this point, you have saving + restoring, you have access to the
- appropriate memory values for ip and sp, now all you need to do is add the
-  saving and restoring of the proper values. what IP are you saving into the
- previous task. save ip by:
-	movl $1f, (%theregisterpointingtoip)
-	movl %esp, (%theregisterpointingtosp)
--	movl %registerholdingnextthreadsp, %esp
-	jmp %registerholdingnextthdip
-	1: asm to return to here
*/

//  called by dispatcher(next->sp, next->ip, ptr_current_sp, ptr_current_ip);
//push %ebp
//mov  %esp, %ebp

	pushal
	// pushal adds 32 bytes to ESP.
	// add 0x20 to all stack vals (first param, 0x04 becomes 0x24, etc.)

	movl 0x30(%esp), %ecx // 	current ip (address of)
	// save off current IP as a label to return to
	movl $1f, (%ecx)


	movl 0x2C(%esp), %edx // 	current sp (address of)
	// save current SP to current thread
	movl %esp, (%edx)

	// *	reuse %ecx, %edx (previously current address to ip & sp) to store
	// next ip & sp. commenting out these next two lines and dereferncing the
	// registers as appropriate should be an initial test of saving the current
	// thread and reinstating that same thread.
	// *	uncommenting the next two lines  should be proper thread context
	// switching.

	movl 0x28(%esp), %ecx // next ip
	movl 0x24(%esp), %edx // next sp

	//move next SP to SP
	movl %edx, %esp

//mov %ebp, %esp
//pop %esp

	//jump to next ip
	jmp %ecx


	1:popal
	  ret




//		mov %ebp, %esp
//		pop %esp

/*
	pushl %eax
	call __lwt_start_test1
	addl $0x04, %esp
*/

