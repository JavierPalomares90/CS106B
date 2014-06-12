/* File: RandomShuffle.cpp
 *
 * A program that uses recursion to randomly scramble the contents of
 * a string.
 */
#include <iostream>
#include <string>
#include "random.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: randomShuffle(string input);
 * Usage: cout << randomShuffle("keith") << endl; // Might get htiek
 * =================================================================
 * Returns a random permutation of the given string.
 */
string randomShuffle(string input);

int main() {
	while (true){
		string toShuffle = getLine("Enter to shuffle: ");
		if (toShuffle == "") break;
		string shuffled = randomShuffle(toShuffle);
		cout << shuffled << endl;
	}
	return 0;
}

string randomShuffle(string input) {
	if( input == ""){
		return "";
	}else{
		int index = randomInteger(0, input.length() - 1);
		string iRemove = input.substr(0, index) + input.substr(index + 1);
		return input[index] + randomShuffle(iRemove);
	}
}

