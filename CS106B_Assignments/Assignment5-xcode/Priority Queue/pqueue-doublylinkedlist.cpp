/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

const string ERROR_MESSAGE = "Queue is empty.";

/* Constructor */
DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
}

/* Destructor */
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head!= NULL){
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

/* Size of list */
int DoublyLinkedListPriorityQueue::size() {
	
	// Shortcut
	if(isEmpty()){
		return 0;
	}
	int size = 0;
	// Iterate across list to find size
	for(Cell* current = head; current != NULL; current = current->next){
		size++;
	}	
	return size;
}

/* If list is Empty */
bool DoublyLinkedListPriorityQueue::isEmpty() {
	//List is empty if the head is NULL
	return head == NULL;
}

/* Adds an element to the list */
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	
	// Cell holding the element
	Cell* cell = new Cell;
	cell->value = value;
	
	// First element added
	if (head == NULL){
		cell->next = NULL;
		cell->previous = NULL;
		head = cell;
		return;
	}
	
	// Prepend cell to the list
	cell->next = head;
	
	// Nothing in front 
	cell->previous = NULL;
	
	// Point the head to the cell
	head->previous = cell;
	
	// Set the head to the cell
	head = cell;
}

/* Returns but does not remove the lowest element from the list */
string DoublyLinkedListPriorityQueue::peek() {
	
	// Error message if the list is empty
	if(isEmpty()){
		error(ERROR_MESSAGE);
	}
	
	// Lowest value
	string result = findMin(head);
	return result;
}

/* Returns and removes the lowest element from the list */
string DoublyLinkedListPriorityQueue::dequeueMin() {
	
	// Error if the list is empty
	if(isEmpty()){
		error(ERROR_MESSAGE);
	}
	
	// Lowest value
	string result = findMin(head);
	
	// Rescan across the cell to remove the cell containing that value
	for(Cell* current = head; current != NULL; current = current->next){
		
		// Found a cell containing that value
		if (current->value == result){
			Cell* before = current->previous;
			Cell* after = current->next;
			
			// Point the previous cell to the one after as long as it's not NULL
			if(before != NULL){
				before->next = after;
			}
			
			// Point the cell after to the one before as long as it's not NULL
			if(after != NULL){
				after->previous = before;
			}
			
			// If the cell is the head mark the next cell as the new head
			if (current == head){
				head = current->next;
			}
			
			// Delete this pointer
			delete current;
			
			// Don't remove all the cells with the same value to allow for duplicates
			return result;
		}
	}
	return result;
}

/* Finds the minimum value in the list */
string DoublyLinkedListPriorityQueue::findMin(Cell* head){
	
	// Initialize the result to be the value of the head
	string result = head->value;
	
	// Scan across the list for the lowest value
	for(Cell* current = head; current != NULL; current = current->next){
		if (current->value < result){
			result = current->value;
		}
	}
	return result;
}
	

