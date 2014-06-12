/*
 * File: Boggle.cpp
 * ----------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * This file is the main starter file for Assignment #4, Boggle.
 */

 
#include <iostream>
#include "gboggle.h"
#include "graphics.h"
#include "grid.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <cctype>
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const string ERROR_MESSAGE = "Enter a new word: ";

/* Function prototypes */

void welcome();
void giveInstructions();
Grid<char> boardSetup();
void shuffleCubes(Vector<string>& cubes);
void displayCubes(Vector<string>& cubes);
char randomLetter(string str);
Vector<string> getCubes();
string playerInput();
string getLetters(Vector<string> cubes);
Set<string> humanTurn(Lexicon& english, Grid<char>& board);
void displayLetters(Grid<char>& board);
bool isValidWord(string word, Grid<char>& board, int rowStart, int colStart);
void computerTurn(Lexicon& english, Grid<char>& board, Set<string>& wordsFound);
void arrangeBoard(Grid<char>& board, string letters);
string upperCase(string str);
string getLetters(Vector<string> cubes);
bool canFormWord(string word, Grid<char> board, int row, int col, Grid<bool>& visit);
void findWord(Lexicon& english, Grid<char>& board, string word, int r, int c, Grid<bool>& visit, Set<string>& wordsFound);
void playOneGame(Lexicon& english);
Grid<bool> visits();
void clearHighlights();


/* Main program */
int main() {
   initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   drawBoard(4,4);
   welcome();
   giveInstructions();
   Lexicon english("EnglishWords.dat");
   string playAgain;
	
   // Allows to play more than one game		
   while (true){
	   if (playAgain == "N") break;
	   playOneGame(english);
	   playAgain = getLine("Play again? (Y/N) ");
	   while ( playAgain != "Y" && playAgain != "N"){
		   playAgain = getLine("Play again? (Y/N) ");
	   }
   }
   return 0;
}

/* Plays one game of Boggle */
void playOneGame(Lexicon& english){
	Grid<char> board = boardSetup();
	Set<string> wordsFound = humanTurn(english,board);
	computerTurn(english, board, wordsFound);
}
	

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

/* Setups the board by returning the board as a Grid*/
Grid<char> boardSetup(){
	Grid<char> result;
	string input = playerInput();
	input = upperCase(input);
	// Size of the board
	result.resize(4, 4);
	
	// Player chose not to input his own letters
	if(input == ""){
		Vector<string> cubes = getCubes();
		shuffleCubes(cubes);
		string letters = getLetters(cubes);
		arrangeBoard(result,letters);
		displayLetters(result);
		//displayCubes(cubes);
	}
	
	//Player inputs his own letters
	else{
		arrangeBoard(result, input);
		displayLetters(result);
	}
	return result;
	
}

/*Converts a string to upper case */
string upperCase(string str){
	for (int i = 0; i < str.length();  i++){
		str[i] = toupper(str[i]);
	}
	return str;
}

/* Arranges the letters onto the board */
void arrangeBoard(Grid<char>& board, string letters){
	int index = 0;
	for (int row = 0; row < board.numRows(); row++){
		for (int col = 0; col < board.numCols(); col++){
			board[row][col] = letters[index];
			index++;
		}
	}
}
			

/* Allows for player input of the letters if wanted */
string playerInput(){
	string input = getLine("Enter your own cubes? Y/N ");
	while(input != "Y" && input != "N"){
		input = getLine("Enter \"Y\" or \"N\" ");
	}
	string result;
	
	// Player enters the letters 
	if(input == "Y"){
		result = getLine("Enter your input:");
		while (result.size() < 16){
			result = getLine("Enter 16 characters.");
		}
		
	// An empty string is returned as a sentinel value	
	}else{
		result = "";
	}
	return result;
}

				   
/* Returns a vector containing the cubes */
Vector<string> getCubes(){
	Vector<string> cubes;
	for (int i = 0; i < 16 ; i++){
		cubes += STANDARD_CUBES[i];
	}
	return cubes;
}
	

/* Shuffles the cubes */
void shuffleCubes(Vector<string>& cubes){
	for (int i = 0; i < cubes.size(); i++){
		int r = randomInteger(i, cubes.size() - 1);
		string holder = cubes[i];
		cubes[i] = cubes[r];
		cubes[r] = holder;
	}
}

/* Displays the letter */
void displayCubes(Vector<string>& cubes){
	// Copy the cubes into a grid
	Grid<string> holder;
	holder.resize(4,4);
	int index = 0;
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < 4; col++){
			holder[row][col] = cubes[index];
			index++;
		}
	}
	
	// Display the cubes
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < 4; col++){
			char letter = randomLetter(holder[row][col]);
			labelCube(row, col, letter);
		}
	}
}

/* Returns a string of random letters from the cubes */
string getLetters(Vector<string> cubes){
	string result;
	for (int i = 0; i < cubes.size(); i++){
		result += randomLetter(cubes[i]);
	}
	return result;
}

/* Returns a random letter from a string */
char randomLetter(string str){
	int n = randomInteger(0, str.size() - 1);
	return str[n];
}

/* Displays the letters onto the board */
void displayLetters(Grid<char>& board){
	for (int row = 0; row < 4; row++){
		for (int col = 0; col< 4; col++){
			labelCube(row, col, board[row][col]);
		}
	}
}

/* Allows for the player's turn */
Set<string> humanTurn(Lexicon& english, Grid<char>& board){
	Set<string> wordsUsed;
	while (true){
		string word = getLine("Enter your words: (Hit Enter 2X to finish): ");
		
		// Makes the word upper case
		word = upperCase(word);
		clearHighlights();
		
		//Player has finished entered their words
		if (word == ""){
			break;
		}
		while(wordsUsed.contains(word)){
			cout << "You've already entered that word." << endl;
			word = getLine(ERROR_MESSAGE);
		}
		if (word.length() < 4){
			cout << "Sorry that word is not long enough." << endl;
			word = getLine(ERROR_MESSAGE);
		}
		if (!english.contains(word)){
			cout << "Sorry that is not a valid English word." << endl;
			word = getLine(ERROR_MESSAGE);
		}
		if (!isValidWord(word, board, 0, 0)){
			cout << "Sorry that word is not on the board." << endl;
			word = getLine(ERROR_MESSAGE);
		}
		
		recordWordForPlayer(word, HUMAN);
		wordsUsed += word; 
	}	
	return wordsUsed;
}

/* Clears highlights for the next word */
void clearHighlights(){
	for (int row = 0 ; row < 4; row++){
		for (int col = 0; col < 4; col++){
			highlightCube(row, col, false);
		}
	}
}

/* Returns true if the word is a valid word on the board */
bool isValidWord(string word, Grid<char>& board, int rowStart, int colStart){
	
	// Search the entire board for the first letter
	for (int row = 0; row < board.numRows(); row++){
		for (int col = 0; col < board.numCols(); col++){
			
			// Grid of false
			Grid<bool> visit = visits();
			if (board[row][col] == word[0]){
				
				// Can form word with adjacent letters
				if (canFormWord(word,board, row, col,visit)){
					return true;
				}
			}
		}
	}
	return false;
}

/* Returns whether a word can be formed by adjacent letters */
bool canFormWord(string word, Grid<char> board, int r, int c, Grid<bool>& visit){
	
	// All elements of the board have been searched over and the word has not been completed
	if ( r == board.numRows() && c == board.numCols() && word != ""){
		return false;
	}
	
	// A word has been fully formed on the board
	if (word == ""){
		return true;
	}
	
	// Look around the elements of the board
	for (int row = r - 1 ; row < r + 2; row++){
		for (int col = c - 1; col < c + 2; col++){
			
			// Keeps indices from going out of bounds
			if (row < 0 || row >= board.numRows() ) continue;
			if (col < 0 || col >= board.numCols() ) continue;
			
			// Begin to form the word
			if(board[row][col] == word[0] && !visit[row][col]){
				visit[row][col] = true;
				string rest = word.substr(1);
				
				// highlights the word
				highlightCube(row, col, visit[row][col]);
				if (canFormWord(rest, board, row , col, visit)){
					return true;
				}else {
					//The letter wasn't used, mark it as unvisited
					visit[row][col] = false;
				}
			}
		}
	}
	return false;				
}
	

/* Allows for the computer's turn */
void computerTurn(Lexicon& english, Grid<char>& board, Set<string>& wordsFound){
	
	for (int row = 0; row < board.numRows(); row++){
		for (int col = 0; col< board.numCols(); col++){
			// Grid of false
			Grid<bool> visit = visits();
			
			// Begin forming a word with board[row][col]
			string start = string() + board[row][col];
			visit[row][col] = true;
			findWord(english, board, start, row, col, visit, wordsFound);
		}
	}	
}

/* Returns a word that can be formed on the board. If no word can be formed returns an empty string as a sentinel value */
void findWord(Lexicon& english, Grid<char>& board, string word, int r, int c, Grid<bool>& visit, Set<string>& wordsFound){
	// The word is an empty path
	if(!english.containsPrefix(word)){
		
		// The previous visit will not be used
		visit[r][c] = false;
	
		// End recursive calls
		return;
	}
	// A valid english word has been formed
	else if (english.contains(word) && word.length() >= 4 && !wordsFound.contains(word)){
		visit[r][c] = false;
		wordsFound += word;
		recordWordForPlayer(word, COMPUTER);
	}
	// Continue down the path to check if there are more words
	for (int row = r - 1; row < r + 2; row++){
		for (int col = c - 1; col < c + 2; col++){
				
			// Keep the indices from going out of bounds;
			if (row < 0 || row >= board.numRows() ) continue;
			if (col < 0 || col >= board.numCols() ) continue;
				
			// The letter has not been visited 
			if (!visit[row][col]){
				visit[row][col] = true;
				string appended = word + board[row][col];
				findWord(english, board, appended, row, col, visit, wordsFound);
				visit[row][col] = false;
					
			}
		}
	}
}

/* Return a grid of bools that will be used to keep track of which words have been visited */
Grid<bool> visits(){
	Grid<bool> visit;
	
	// Same size as the board
	visit.resize(4,4);
	for (int row = 0; row < visit.numRows(); row++)	{
		for (int col = 0; col < visit.numCols(); col++){
			visit[row][col] = false;
		}
	}
	return visit;
}




		
					

	

	