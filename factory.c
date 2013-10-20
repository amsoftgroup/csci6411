

/*
 * Factories expose functions that create and manage threads.
 *
 * Factories have, and share among threads:
 *  Stack Pointer
 *  Program Counter
 *  Registers
 */
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"




/* Stack Pointer
 *
 * see http://en.wikipedia.org/wiki/Call_stack

   Our call_stack will contain:
	a struct of all local variables and return address
	a pointer to the stack
	a pointer to the frame
*/
struct local_variables local_vars[];
struct node* call_stack_head = NULL;
struct node* stack_pointer = NULL;
struct node* frame_pointer = NULL;


/* Program Counter
 *
 * http://en.wikipedia.org/wiki/Program_counter

   Our program counter will contain:
	a pointer in a linkedlist of all function calls
*/
struct node* instruction_pointer = NULL;

/* Registers
 *
 * see http://en.wikipedia.org/wiki/Processor_register

   Our processor_register will contain:

*/

