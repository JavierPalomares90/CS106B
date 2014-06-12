/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file implements and tests the intToString() and stringToInt() 
 * functions.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);



/* Main program. Used to test intToString() and stringToInt() methods */
int main() {
	int num = getInteger("Enter a number to convert to int: ");
	string str = getLine("Enter a number to convert to str: ");
	cout << "The int is: " << intToString(num) << endl;
	cout << "The string is: " << stringToInt(str) << endl;
    return 0;
}

/* Converts a integer string to its string representation */
string intToString(int n){
	// Negative number
	if (n < 0){
		string negSign = "-";
		// Find intToString of pos. number and then concatinate "-" to the result.
		return negSign + intToString((-1) * n);
	// Single digit non-negative integer	
	} else if (0 <= n && n < 10){
		char ch = char(n + '0');
		return string() + ch;
	// Recursive algorithm	
	} else{
		return intToString(n / 10) + intToString (n % 10);
		
	}
}

/* Converts a numeric string to its integer representation */
int stringToInt(string str){
	// String of a negative number
	if (str[0] == '-'){
		return -1 * stringToInt(str.substr(1));
	// Single digit string	
	}if(str.length() == 1){
		return int(str[0] - '0');
	// Recursive algorithm
	}else{
		return stringToInt(str.substr(0, str.length() - 1)) * 10 + int(str[str.length() - 1] - '0') ;
	}
}
						   

