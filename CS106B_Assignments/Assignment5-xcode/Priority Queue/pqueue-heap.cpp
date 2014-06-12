/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"

#include "error.h"



const int MIN_SIZE = 4;
const string DUMMY = "zzzz";

/* Constructor */
HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 0;
	allocatedLength = MIN_SIZE;
	elems = new string[allocatedLength + 1];
	
	// Dummy entry to avoid zero indexing
	elems[0] = DUMMY;
}

/* Destructor */
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] elems;
}

/* Returns size of the queue */
int HeapPriorityQueue::size() {
	return logicalLength;
}

/* Returns whether the queue is empty */
bool HeapPriorityQueue::isEmpty() {
	return logicalLength == 0;
}

/* Adds a word to the queue */
void HeapPriorityQueue::enqueue(string value) {
	if (logicalLength == allocatedLength){
		grow();
	}
	logicalLength++;
	
	// Inserts the element at the last position
	elems[logicalLength] =  value;
	// Bubble Sorts parents and children
	bubbleSort();
}

/* Returns but does not remove the lowest element from the list */
string HeapPriorityQueue::peek() {
	if (isEmpty()){
		error("Queue is empty");
	}
	return elems[1];
}

/* Returns and removes the lowest element from the list */
string HeapPriorityQueue::dequeueMin() {
	if (isEmpty()){
		error("Queue is Empty");
	}
	
	// The result is the first element
	string first = elems[1];
	
	// Swap the first element with the last
	string last = elems[logicalLength];
	elems[1] = last;
	
	// Set the last element to the dummy variable
	elems[logicalLength] = DUMMY;
	
	// Bubble Down
	bubbleDown();
	logicalLength--;
	
	return first;
}

/* Grows the array if there is no more space to insert the new element */
void HeapPriorityQueue::grow(){
	
	// Double the allocated length
	allocatedLength *= 2;
	
	// Create a new array of twice the size. + 1 to allow for the dummy index;
	string* newElems =  new string[allocatedLength + 1];
	
	// Copy the values
	for (int i = 0; i <= logicalLength; i++){
		newElems[i] = elems[i];
	}
	// Set the rest of the values to the dummy variable
	for (int i = logicalLength + 1; i < allocatedLength; i ++){
		newElems[i] = DUMMY;
	}
	
	// Delete the old array
	delete[] elems;
	
	// Set elems to be the new array
	elems = newElems;
}

/* Bubble sorts up the parents and children */
void HeapPriorityQueue::bubbleSort(){
	
	// Start at the child that was just added to elems[logicalLength] and compare to the parent at logicalLength / 2.
	// Stop the loop if the index gets to 1 since it doesn't have a parent
	for (int i = logicalLength; i != 1; i--){
		string parent = elems[i / 2];
		string child = elems[i];
		if (child < parent){
			
			// Swap postions of parent and child
			elems[i / 2] = child;
			elems[i] = parent;
		}
	}
}

/* Bubble sorts down after swapping the first and last elements */
void HeapPriorityQueue:: bubbleDown(){
	int i = 1;
	while (true){
		if (2 * i + 1 > logicalLength){
			break;
		}
		string parent = elems[i];
		
		// The two children
		string child1 = elems[2 * i];
		string child2 = elems[2 * i + 1];
		
		// Find which child to swap for
		if( child1 < child2 && child1 < parent){
			elems[i] = child1;
			elems[2 * i] = parent;
			i *= 2;
		}else if (child2 <= child1 && child2 < parent)  {
			elems[i] = child2;
			elems[2 * i + 1] = parent;
			i = 2 * i + 1;
		}
		
		// The parent is smaller than both children, bubble sort is done
		else{
			break;
		}
	}
}
	

