.text
.align 16
.globl dispatcher
dispatcher:

/* caller saves registers to stack */
push %ebp
mov  %esp, %ebp


// use these two registers to store next and current TCB
//push %eax
//push %ebx

	movl 0x08(%ebp), %eax // CURRENT, 2nd param stack address
	movl 0x0C(%ebp), %ebx // NEXT, 1st param stack address
/*
//uncomment to show proper mem locations are passed in
	push 0x08(%ebp)
	push 0x0C(%ebp)
	 call __lwt_start_test2
*/

/*
// push 32 bit regsiters
	push %eax
	push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi
*/

// movl current registers to 1st parameter location [0x08(%ebp)]
// 32 bit registers
	movl %eax, 0x08(%eax)

	push 0x08(%eax) 		// testing
	call __lwt_start_test2  // testing

	movl %ebx, 0x0C(%eax)
	movl %ecx, 0x10(%eax)
	movl %edx, 0x14(%eax)
	movl %esi, 0x18(%eax)
	movl %edi, 0x1C(%eax)


// 16 bit registers
	mov %ss,  0x20(%eax)
	mov %ds,  0x22(%eax)
	mov %es,  0x24(%eax)
	mov %fs,  0x26(%eax)
	mov %gs,  0x28(%eax)

// mov next thread's registers from 2nd parameter location [0x0C(%ebp)]

	//movl 0x08(%ebx), %eax

	push 0x08(%ebx)



	movl 0x0C(%ebx), %ebx
	movl 0x10(%ebx), %ecx


	//movl 0x14(%ebx), %edx
	//movl 0x18(%ebx), %esi
	//movl 0x1C(%ebx), %edi

// 16 bit registers

	//mov 0x20(%ebx), %ss
	//mov 0x22(%ebx), %ds
	//mov 0x24(%ebx), %es
	//mov 0x26(%ebx), %fs
	//mov 0x28(%ebx), %gs

 mov %ebp, %esp

 //pop %esp
 //pop %esp

 pop %ebp

ret
	//movl %ecx, %eax
	//movl %edx, (0x04)%eax


	//undo next  and current assignments
	//pop  %ebx
	//pop  %eax

	// push all our registers

/* call to C function with above parameters, demonstrating basic understanding of cdecl */
	//call *0x08(%ebp)

/* restore our registers */
//mov %ebp, %esp
//pop %ebp
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
