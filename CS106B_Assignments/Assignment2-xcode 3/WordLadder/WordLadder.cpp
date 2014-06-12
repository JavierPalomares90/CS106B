/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file takes in a start and an end word and returns the shortest word ladder between the two.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

Vector<string> wordLadder(string start, string end);
Vector<string> wordsThatDifferByOneLetter(string word);
bool vectorHasFinalWord(Vector<string> vect, string str);
bool vectorContains(Vector<string> vect, string str);
Vector<string>  noLadderFound();

const int NUM_LETTERS_IN_ALPHABET = 26;

/* Main program */
int main() {
	cout <<  '1' + 8 << endl;
	//string start = getLine("Enter a word (Return to quit): ");
//	string end = getLine("Enter destination word: ");
//	Vector<string> ladder = wordLadder(start,end);
//	foreach(string word in ladder){
//		cout << word << " " ;
//	}
	return 0;
}

/* Returns a vector containing all the words in English that differ by one letter */
Vector<string> wordsThatDifferByOneLetter(string word){
	// Lexicon of words in English
	Lexicon english("EnglishWords.dat");
	// Will contain all the words that differ by one letter
	Vector<string> words;
	for(int i = 0; i < word.size(); i++){
		for(int alpha = 0; alpha < NUM_LETTERS_IN_ALPHABET; alpha++){
			string testWord = word;
			// Changes the character at position i to a differ letter
			testWord[i] = 'a' + alpha;
			if(english.contains(testWord)){
				words += testWord;
			}
		}
	}
	return words;
}
			


/* Returns vector containing the shortest word latter */
Vector<string> wordLadder(string start, string end){
	//Queue containing possible ladders as vectors
	Queue<Vector<string> > queue;
	// Vector used as a placeholder to add the start word 
	Vector<string> startVect;
	startVect += start;
	Vector<string> wordsUsed;
	queue.enqueue(startVect);
	while(!queue.isEmpty()){ 
		Vector<string> vect = queue.dequeue();
		if(vectorHasFinalWord(vect,end)){
			return vect;
		}
		Vector<string> newWords = wordsThatDifferByOneLetter(vect[vect.size() - 1]);
		foreach(string words in newWords){
			// The word has not been used in a previous ladder
			if(!vectorContains(wordsUsed, words)){
				Vector<string> copy = vect;
				copy += words;
				queue.enqueue(copy);
				wordsUsed += words;
			}
		}
	}
	// No ladder found
	Vector<string> noLadder = noLadderFound();
	return noLadder;;
}

/* Checks whether a string is the final element a vector */
bool vectorHasFinalWord(Vector<string> vect, string str){
	return vect[vect.size() - 1] == str;
}
															 
/* checks whether a string is in a vector */															 
bool vectorContains(Vector<string> vect, string str){
	for( int i = 0; i < vect.size(); i++){
		if(vect[i] == str){
			return true;
		}
	}
	return false;
}

//* No word ladder found */
Vector<string> noLadderFound(){
	Vector<string> result;
	result += "No";
	result += "ladder";
	result += "found";
	return result;
}