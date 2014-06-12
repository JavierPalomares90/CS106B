/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"


/* Constructor for VectorPriorityQueue */
VectorPriorityQueue::VectorPriorityQueue() {
	Vector<string> queue;
}

/* Deconstructor is mananged by the deconstructor of vector */
VectorPriorityQueue::~VectorPriorityQueue() {
}

/* Returns the size of the queue */
int VectorPriorityQueue::size() {
	return queue.size();
}

/* Whether the queue is empty */
bool VectorPriorityQueue::isEmpty() {
	return queue.isEmpty();
}

/* Adds and element to the queue */
void VectorPriorityQueue::enqueue(string value) {
	queue += value;
}

/* Returns but does not remove the least element */
string VectorPriorityQueue::peek() {
	if (size() == 0){
		error("Queue is empty");
	}
	
	// Will initialize the result to the first element in the collection
	string result = queue[0];
	
	// Scan across the loop for the lowest element
	for (int i = 0; i < queue.size(); i++){
		if (queue[i] < result){
			result = queue[i];
		}
	}
	return result;
}

/* Returns and removes the least element */
string VectorPriorityQueue::dequeueMin() {
	if (size() == 0){
		error("Queue is empty");
	}
	int index = 0;
	string result = queue[0];
	for (int i = 0; i < queue.size(); i++){
		if (queue[i] < result){
			result = queue[i];
			index = i;
		}
	}
	queue.removeAt(index);
	return result;
}



	

