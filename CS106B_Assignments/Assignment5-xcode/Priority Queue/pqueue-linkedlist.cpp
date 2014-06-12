/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"
#include <iostream>

/* Constructor for collection */
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
}

/* Destructor */
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

/* Size of collection */
int LinkedListPriorityQueue::size() {
	int result = 0;
	
	// Iterate over the list 
	for (Cell* curr = head; curr != NULL; curr = curr->next) {
		result++;
	}
	return result;
}

/* collection is empty if the head of the collection is null */
bool LinkedListPriorityQueue::isEmpty() {
	return head == NULL;
}

/* Adds elements to the collection in sorted order */
void LinkedListPriorityQueue::enqueue(string str) {
	// New cell to store value
	Cell* cell = new Cell;
	cell->value = str;
	
	// First element entered
	if (head == NULL){
		cell->next = NULL;
		head = cell;
		return;
	}
	
	// Pointers to insert link
	Cell* previous = NULL;
	Cell* current;
	
	// Scan over the list
	for(current = head; current!= NULL; current = current->next){
		
		// break at the first list list that has a value greater than the cell's value
		if (cell->value < current->value){
			break;
		}
		previous = current;
	}
	
	// Point the cell to the one immediately greater
	cell->next = current;
	
	// Point the one immediately less to the cell as long as its not NULL.
	if (previous!= NULL){
		previous->next = cell;
		
	// If the one immediately less is NULL then the cell is the nuew head	
	}else{
		head = cell;
	}	
}

/* Returns the first element since they are stored in sorted order */
string LinkedListPriorityQueue::peek() {
	
	// Error if the collection is empty
	if (isEmpty()){
		error("Queue is Empty");
	}
	return head->value;
}

/* Returns and removes the first element from the collection */
string LinkedListPriorityQueue::dequeueMin() {
	
	//Error if collection is empty
	if (isEmpty()){
		error("Queue is Empty");
	}
	// Value to return
	string result = head->value;
	
	//Remove the element from the list
	head = head->next;
	
	return result;
}

