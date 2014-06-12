/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int combinations(int n, int k);
/* Main program. For loops are used only to generate the pyramid. combinations(n,k) uses a purely recursive implementation */
int main() {
	// Number of rows in pyramid
	int numRows = 10;
	// Iterate over rows
	for(int n = 0; n < numRows;  n++){
		// Iterate over entries in row
		for(int k = 0; k <= n; k++){
			cout << combinations(n,k)<<" " ;
		}
		cout<< ""<< endl;
	}
   return 0;
}

// Computes the c(n,k)
int combinations(int n, int k){
	// Return 1 if it's the top of the pyramid or along the edges
	if (n == 0 || n == 1 || k == 0 || k == n){
		return 1;
	// Recursive algorithm	
	}else{
		return combinations(n - 1, k - 1) + combinations( n - 1, k);
	}
}