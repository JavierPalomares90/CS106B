/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This program reads in a source file and returns randomly generated text of a given order Makarov model
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

string promptUserForFile(ifstream& infile, string prompt);
Map<string, Vector<char> > readFile(ifstream& infile, int order);
string getMode(Map<string, Vector<char> > frequency);
void randomText(string mode, Map<string, Vector<char> > frequency, int order);
char nextChar(string sequence, Map<string, Vector<char> > frequency);

/* Main program */
int main() {
	ifstream infile;
	promptUserForFile(infile, "Input file: ");
	int order = getInteger("Enter the order: ");
	Map<string, Vector<char> > frequency = readFile(infile,order);
	string initialSequence = getMode(frequency);
	randomText(initialSequence, frequency, order);
	return 0;
}

/* Prompts user for file until an acceptable file name is entered. This code was taken from the CS106B course reader page 172*/
string promptUserForFile(ifstream& infile, string prompt) { 
	while (true) {
		cout << prompt; 
		string filename; 
		getline(cin, filename); 
		infile.open(filename.c_str()); 
		if (!infile.fail()) 
			return filename; 
		infile.clear(); 
		cout << "Unable to open that file. Try again." << endl; 
		if (prompt == "") 
			prompt = "Input file: ";
	}
}

/* Returns the frequency map for sequences in the file */
Map<string, Vector<char> > readFile(ifstream& infile, int order){
	Map<string, Vector<char> > frequency;
	char ch;
	while (infile.get(ch)){
		string sequence;
		sequence += ch;
		// Creates a sequence of appropriate order
		for(int i = 0; i < order - 1 ; i++){
			char nextChar;
			infile.get(nextChar);
			sequence += nextChar;
		};
		// Adds the character sequence of order size to the frequency table with the next character as the value
		frequency[sequence] += infile.get();
		// Backs up the character index for the next sequence
		for(int i = 0; i < order; i++){
			infile.unget();
		}
	}	
	return frequency;
}

/* Returns the most common sequence in a the frequency map */
string getMode(Map<string, Vector<char> > frequency){
	string mode;
	int numFrequencies;
	foreach(string sequence in frequency){
		if(!frequency.containsKey(mode)){
			numFrequencies = 0;
		}else{
			numFrequencies = frequency.get(mode).size();
		}
		   
		if(frequency.get(sequence).size() > numFrequencies){
			mode = sequence;
		}
	}
	return mode;
}


/* Generates random text */
void randomText(string str, Map<string, Vector<char> > frequency, int order){
	// Initial character of the first sequence is at 0
	int charPosition = 0;
	while(str.length() < 2000){
		string subString = str.substr(charPosition, order);
		// If the key is not in the map, such as when the sequence is the end of the file, break
		if(!frequency.containsKey(subString)){
			break;
		}
	    // Character to Append to sequence
		char ch = nextChar(subString, frequency);
		str += ch;
		charPosition++;
	}
	cout << str;
}
	
/* Generates a random characters to add to the text */
char nextChar(string sequence, Map<string, Vector<char> > frequency){
	//cout << "Sequence: " << sequence << endl;
	Vector<char> characters = frequency.get(sequence);
	int i = randomInteger(0, characters.size() - 1);
	// Returns random character that follows the sequence
	//cout << "Character to Append: " << characters[i] << endl;
	return characters[i];
}
	
				

	

