
#ifndef FACTORY_H
#define FACTORY_H

typedef struct lightweight_thread_struct{
	int id;
	struct lightweight_thread *next;
	struct node* stack;
	struct node* instr;
} *lwt_t;



#endif
