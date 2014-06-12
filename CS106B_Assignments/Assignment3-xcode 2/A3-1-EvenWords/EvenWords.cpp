/* File: EvenWords.cpp
 *
 * A program that uses recursion to determine which words are
 * even words.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: isEvenWord(string input);
 * Usage: if (isEvenWord("tattletale")) { ... }
 * ==================================================================
 * Returns whether the given word is an "even word;" that is, whether
 * every letter in the word appears an even number of times.
 */
bool isEvenWord(string word); 

/* Main program */
int main() {
	while (true) {
		string word = getLine("Enter a word: ");
		if(word == "") break;
		if(isEvenWord(word)){
			cout << "true"<< endl;
		}
		else {
			cout << "false" << endl;
		}
	}	
	return 0;
}

/* Returns whether a word is even */
bool isEvenWord(string word){
	if (word == ""){
		return true;
	}else {
		string iRemoved = word;
		
		// Shorten the string by removing the first letter
		char toRemove = iRemoved[0];
		
		// Number of times 'toRemoved' is removed in the chose
		int numLettersRemoved = 0;
		
		// Remove all of chars 'toRemove' in the word
		for (int index = 0; index < iRemoved.length(); index++){
			if (iRemoved[index] == toRemove){
				iRemoved.erase(index,1);
				numLettersRemoved++;
				
				//If we remove a letter, index must be backed up or the next char will be skipped
				index--;
			}
		}
		
		// If there is an odd number of 'toRemove' the word is not even
		if (numLettersRemoved % 2 == 1){
			return false;
		}
		return isEvenWord(iRemoved);
	}
}
			
