/*
 * File: path.cpp
 * --------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file implements the path.h interface.
 */

/////////////////////////////////////////////////////////////////////
// Path.h uses a the vector class as the hear of this implementation. 
// The Vector is used to hold the Arc*, but the class also implements
// a private instance variable totalCost whose value can be passed by 
// calling .cost(). This is efficient as it avoids having to calculate 
// the cost of each path one by one. Adding and removing elements 
// from the path updates the totalCost of the altered path. The path 
// also has some of the functions interfaced by the vector class which
// are implemented by calling the analogous function on the vector.
// I decided to use a vector as it avoids having to work with dynamic
// memory arrays, and the vector's implementation of memory management
// works extremely well for this case. 
/////////////////////////////////////////////////////////////////////


#include "path.h"

/* Constructor for the path */
Path::Path(){
	totalCost = 0;
}

/* Destructor for the path is handeled by the destructor the the vector */
Path::~Path(){
}

/* Appends a node to the path */
void Path::add(Arc* a){
	arcs += a;
	totalCost += a->cost;
}

/* Returns the size of the path */
int Path::size(){
	return arcs.size();
}

/* Returns the total cost of a path */
double Path::cost(){
	return totalCost;
}

/* Returns a string composed of the nodes on the path separated by arrows formed by the two-character sequence ->. */
string Path::toString(){
	string result = arcs[0]->start->name;
	for(int i = 0; i < arcs.size(); i++){
		result = result + "->" + arcs[i]->finish->name;
	}
	return result;
}

/* Cuts the last city */
void Path::removeAt(int i){
	// If the city is removed from the path subtract its cost
	totalCost = totalCost - arcs[i]->cost;
	arcs.removeAt(i);
}

/* Removes all cities from the path */
void Path::clear(){
	arcs.clear();
}

/* Returns the element at position i */
Arc* Path::get(int i){
	return arcs[i];
}
