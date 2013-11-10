.text
.align 16
.globl dispatcher
dispatcher:

/*
- formula for doing all of this:
- you need the sp and the ip you want to switch to (can pass as arguments)
- you need the address of the sp and ip you are switching away from so that you can save those to the proper locations
- within the assembly, you are worried about 1) reading and writing those values, which you can test by making this function "normal" (no switching), and 2) saving and restoring the "proper" values.
- you can add saving and restoring logic for normal registers before adding switching
- At this point, you have saving + restoring, you have access to the appropriate memory values for ip and sp, now all you need to do is add the saving and restoring of the proper values.
- what IP are you saving into the previous task
-	save ip by:
-	movl $1f, (%theregisterpointingtoip)
-	movl %esp, (%theregisterpointingtosp)
--	movl %registerholdingnextthreadsp, %esp
-	jmp %registerholdingnextthdip
-	1: asm to return to here
*/


push %ebp
movl %esp, %ebp

pushal

//  called by dispatcher(next->sp, next->ip, current->sp, current->ip);


	movl $1f,  0x14(%ebp)
	movl %esp, 0x10(%ebp)
	movl 0x08(%ebp),  %esp
	jmp  0x0C(%ebp)

	1:
// clean up
call __lwt_start_test0
popal
movl %ebp, %esp
pop %ebp

ret
	//call __lwt_start_test0
//	movl 0x04(%esp), %eax //	next sp
//	movl 0x08(%esp), %ebx //	next ip
//	movl 0x0C(%esp), %ecx // 	current sp
//	movl 0x10(%esp), %edx //	current ip
/*
	push $99
	push %eax
	push %ebx
	push %ecx
	push %edx
	call __lwt_start_test5
*/

	// copy params to registers

	//movl 0x08(%ebp), %eax //	next sp
	//movl 0x0C(%ebp), %ebx //	next ip
	//movl 0x10(%ebp), %ecx // 	current sp
	//movl 0x14(%ebp), %edx //	current ip


/*
Here are the important processor registers:

    EAX,EBX,ECX,EDX - "general purpose", more or less interchangeable

    EBP             - used to access data on stack
                    - when this register is used to specify an address, SS is
                      used implicitly

    ESI,EDI         - index registers, relative to DS,ES respectively

    SS,DS,CS,ES,FS,GS - segment registers
                      - (when Intel went from the 286 to the 386, they figured
                         that providing more segment registers would be more
                         useful to programmers than providing more general-
                         purpose registers... now, they have an essentially
                         RISC processor with only _FOUR_ GPRs!)
                      - these are all only 16 bits in size

    EIP            - program counter (instruction pointer), relative to CS

    ESP            - stack pointer, relative to SS

    EFLAGS         - condition codes, a.k.a. flags

*/
