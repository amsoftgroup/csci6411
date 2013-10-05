/*
 * linkedlist.h
 *
 *  Created on: Sep 11, 2013
 *      Author: cos
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct local_variables{
	int return_address;
	// more local vars declared below
	// ...

};

struct node {
	struct local_variables vars;
	struct node* next;
};

void PushToHead(struct node** headRef, struct local_variables newData);
void AppendToTail( struct node** headRef, int num);
int Length(struct node* head);
int PopFromHead(struct node** headRef);

#endif /* LINKEDLIST_H_ */
