/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file converts a word to Obenglobish.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;


string obenglobish(string str);
bool isVowel(char ch);
bool isDoubleVowel(char previous, char current, int i);
bool isSilentE(int i, string str);

/* Main program */
int main() {
	while (true){
		string word = getLine("Enter a word: ");
		//cout << word<< endl;
		if (word == ""){
			break;
		}
		string trans = obenglobish(word);
		cout << word << " -> " << trans << endl;
	}
   return 0;
}

/* Converts an english word to obengoblish */
string obenglobish(string str){
	string ob = "ob";
	string result;
	char previous = str[0];
	char current;
	for(int i = 0; i < str.length(); i++){
		current = str[i];
		// Add "ob" only if the letter is a vowel, not a silent e, and not a double vowel
		if (isVowel(current) && !isSilentE(i,str) && !isDoubleVowel(previous, current, i)){
			result += ob + current;
		// Continue the word	
		}else{
			result += current;
		}
		previous = current;
	}	
	return result;	   
}


		
/* Checks if the char is a vowel */
bool isVowel(char ch){
	if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
		return true;
	}
	return false;
}

/* Checks if there is a doubleVowel */
bool isDoubleVowel(char previous, char current, int i){
	// when i = 0, current == previous, ignore test 
	if(i == 0){
		return false;
	}
	// true if both previous and current are vowels
	if(isVowel(previous) && isVowel(current)){
		return true;
	}
	return false;
}

/* Checks if there's a silent e */
bool isSilentE(int i, string str){
	// Only return true if the last char is an 'e'
	if(i == str.length() - 1 && str[i] == 'e'){
		return true;
	}
	return false;
}