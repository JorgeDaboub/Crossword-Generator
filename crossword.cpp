// Main Crossword puzzle
// By: Jorge Daboub

#include<iostream>
#include<string>
#include<vector>
#include"cross.h"
using namespace std;

int main(int argc, char *agrv[]) {
	// Defining the game from class
	Board game;
	if(argc > 3) {
		cout << "Entered too many inputs." << endl;
		return 1;
	}
	else if(argc > 1) {

		cout << endl << "Anagram Crossword Puzzle Generator" << endl;
		cout << "----------------------------------" << endl << endl;
		// Reading in input from file
		game.readInFile(agrv[1]);
		// Generating the board (game)
		game.make();
		
		// If no output provided disaply on screen
		if(argc == 2)
			game.display();
		// Else output to  file
		else {	
			game.toFile(agrv[2]);
			cout << "Game saved to file: " << agrv[2] << endl;
		}
	}
	else {
		cout << endl << "Anagram Crossword Puzzle Generator" << endl;
		cout << "----------------------------------" << endl << endl;
		cout << "Please enter the words for the crossword followed by a \".\"" << endl;
		
		// User input of words manualy
		game.readIn();
		// Make and display the game
		game.make();
		game.display();
	}
	return 0;
}
