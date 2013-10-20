#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "thread.h"
#include "linkedlist.h"

/*
 * Linked List implementation from "Linked List Basics", by Nick Parlante
 * as appears in CS6411 course web page. I understand we were not to copy
 * code from the Internet, but this was expressly provided as part of our
 * course materials...
 */


void PushToHead(struct node** headRef, int data) {

	struct node* current;
	current = malloc(sizeof(struct node));
	//current = *headRef;


	printf("LL: data=%i /n", data);

	struct node *newNode;
	newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;

	//struct node *current = *headRef;



	if (headRef == NULL){
		printf("LL: NULL LINKEDLIST! Adding as head");
		// create a new head
		//*headRef = newNode;
	}else{
		printf("LL: head exists, but has no next");
		// head exists, but has no next
		//newNode->next = *headRef;
		//*headRef = newNode;
	}

}

void AppendToTail(struct node** headRef, int num) {
//void AppendToTail(struct node** headRef, lwt_t num) {
	struct node* current = *headRef;
	// special case for the empty list
	if (current == NULL) {
		PushToHead(headRef, num);
	} else {
		// Locate the last node
		while (current->next != NULL) {
			current = current->next;
		}
		// Build the node after the last node
		PushToHead(&(current->next), num);
	}
}

// Return the number of nodes in a list
int Length(struct node* head) {
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current=current->next;
    }
    return(count);
}


int PopFromHead(struct node** headRef) {
	struct node* head;
	int result;
	head = *headRef;
	result = head->data; // pull out the data before the node is deleted
	*headRef = head->next;
	free(head); // free the head node
	return(result); // don't forget to return the data from the link
}

