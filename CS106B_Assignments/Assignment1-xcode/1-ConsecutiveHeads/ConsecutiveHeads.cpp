/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file simulates a coin flip until there are 3 heads in a row. 
 * It then gives the number of tries.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;


int flipCoin(int heads);

int main(){
	// Number of tries
	int tries = 0;
	// Number of heads in a row
	int heads = 0;
	while (heads < 3 ){ 
		heads = flipCoin(heads);
		tries ++;
	}
	cout<< "It took " << tries << " tries to get 3 heads in a row."<< endl;
	return 0;
}

int flipCoin(int heads){
	// Random generated number between 1 and 10
	int coin = randomInteger(1,10);
	// Simulation of heads
	if (coin <= 5){
		cout << "heads" << endl;
		// One more head in a row
		return heads + 1 ;
	// Simulation of tails	
	}else{
		cout << "tails" << endl;
		// Resets number of heads in a row
		return 0;
	}
}

