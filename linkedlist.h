/*
 * linkedlist.h
 *
 *  Created on: Sep 11, 2013
 *      Author: cos
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

//#include "thread.h"

typedef struct node {
	int data;
	struct node* next;
} node;

void PushToHead(struct node** headRef, int data);
void AppendToTail(struct node** headRef, int num);
int Length(struct node* head);
int PopFromHead(struct node** headRef);

#endif /* LINKEDLIST_H_ */
