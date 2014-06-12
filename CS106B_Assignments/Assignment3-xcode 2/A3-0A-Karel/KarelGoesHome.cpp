/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the KarelGoesHome problem.
 */

#include <iostream>
#include <iomanip>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

int countPaths(int street, int avenue);

/* Main program */

int main() {
	while(true){
		int street = getInteger("Street(Enter 0 to quit): ");
		if (street == 0) break;
		int avenue = getInteger("Avenue: ");
		int numPaths = countPaths(street,avenue);
		cout << "The number of paths is :" << numPaths << endl;
	}
   return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

/* Returns the number of shortest paths home */
int countPaths(int street, int avenue) {
	// If Karel is on first avenue or first street, there is only one way: go straight home
	if( street == 1|| avenue == 1){
		return 1;
	}
	else{
		return 2 + countPaths(street - 1, avenue - 1);
	}
   // [Fill this in]
}
