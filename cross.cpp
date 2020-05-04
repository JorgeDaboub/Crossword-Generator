// Crossword Header file
// By: Jorge Daboub

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<ctype.h>
#include<utility> 
#include"cross.h"

using namespace std;

Board::Board() {
	// Empty Board
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++)
			board[i][j] = '.';
}
Board::~Board() {}

void Board::display() {
	// Displaying the board
	cout << "Solution: " << endl;
	for(int i = 0; i < len+2; i++) {
		if((i == 0) || (i == len+1)) { 
			cout << " ";
			for(int k = 0; k < len; k++)
				cout << "-";
			cout << endl;
		}
		else {
			cout << "|";
			for(int j = 0; j < len; j++)
				cout << board[i-1][j];
			cout << "|" << endl;
		}
	}

	cout << endl << "Puzzle:" << endl;
	for(int i = 0; i < len+2; i++) {
		if((i == 0) || (i == len+1)) {
			cout << " "; 
			for(int k = 0; k < len; k++)
				cout << "-";
			cout << endl;
		}
		else {
			cout << "|";
			for(int j = 0; j < len; j++) {
				if(board[i-1][j] == '.')
					cout << "#";
				else
					cout << " ";
			}
			cout << "|" << endl;
		}
	}

	// Displaying the clues for the words
	cout << endl << "Clues: " << endl;
	cout << "Location | Direction | Anagram" << endl;

	for(int i = 0; i < Clues.size(); i++) {

		cout << right << setw(5) << Clues[i].r << "," << setw(2) << Clues[i].c;
		cout << " |";
		if(Clues[i].z == 0)
			cout << "    Across | ";
		else
			cout << "      Down | ";

		cout << left << Clues[i].a << endl;
	}
	cout << endl;
	// Displaying words that could not be palced.
	for(int i = 0; i < notPlaced.size(); i++)
		cout << notPlaced[i] << " could not be placed." << endl;

}

void Board::sort() {
	for(int i = 0; i < words.size(); i++){
		string temp = words[i];
		int j = i - 1;
		// Ordering all the words from largest to smalest
		while(j >= 0 && temp.length() > words[j].length()) {
			words[j+1] = words[j];
			j--;
		}
		words[j+1] = temp;
	}
}

void Board::addWord(string word) {
	// Adding all inputs as capital letters
	for(int i = 0; i < word.size(); i++)
		word[i] = ::toupper(word[i]);

	words.push_back(word);
}

void Board::readIn() {
	string input;
	// Reading in from user
	int i = 20;
	while(i > 0){
		// Flag in case there is an invalid entry
		bool flag = false;
		getline(cin,input);

		if(input.size() == 1) {
			if(input == ".")
				break;
			cout << "Single characters cannot be entered." << endl;
			flag = true;
		}
		else {
			if(input.size() > 15) {
				cout << input << " is longer than 15 characters" << endl;
				flag = true;
			}
			for(auto i : input)
				if(!isalpha(i)) {
					cout << "Invalid character \"" << i << "\"" << " entered." << endl;
					flag = true;
				}
		}
		// If no errors then add the word
		if(!flag) {
			addWord(input);
			i--;
		}
		// Else do not add the word and print an error message.
		else
			cout << "Entry \"" << input << "\" will be ignored." << endl; 
	}
}

void Board::readInFile(string fileName) {
	string input = "";

	ifstream ifs;
	ifs.open(fileName);

	// Bad file name
	if(!ifs) {
		cout << "Bad file name: " << fileName << endl;
		exit(10);
	}

	int i = 20;
	do {
		getline(ifs,input);
		// Same logic as for user inputs, raise flag if there is an issue.
		bool flag = false;

		if(input == "")
			flag = true;

		if(input.size() == 1) {
			if(input == ".")
				break;
			cout << "Single characters cannot be entered." << endl;
			flag = true;
		}
		else {
			if(input.size() > 15) {
				cout << input << " is longer than 15 characters" << endl;
				flag = true;
			}
			for(auto i : input)
				if(!isalpha(i)) {
					cout << "Invalid character \"" << i << "\"" << " entered." << endl;
					flag = true;
				}
		}
		// Same logic as for user input
		if(!flag) {
			addWord(input);
			i--;
		}
		else
			cout << "Entry \"" << input << "\" will be ignored." << endl; 

	} while(ifs && (i > 0)); 
	ifs.close();
}


void Board::toFile(string outFile) {

	ofstream ifs;
	ifs.open(outFile);
	// Same layout as display function
	// Just outputing to a filestream instead of the terminal
	ifs << "Solution: " << endl;
	for(int i = 0; i < len+2; i++) {
		if((i == 0) || (i == len+1)) { 
			ifs << " ";
			for(int k = 0; k < len; k++)
				ifs << "-";
			ifs << endl;
		}
		else {
			ifs << "|";
			for(int j = 0; j < len; j++)
				ifs << board[i-1][j];
			ifs << "|" << endl;
		}
	}

	ifs << endl << "Puzzle:" << endl;
	for(int i = 0; i < len+2; i++) {
		if((i == 0) || (i == len+1)) {
			ifs << " "; 
			for(int k = 0; k < len; k++)
				ifs << "-";
			ifs << endl;
		}
		else {
			ifs << "|";
			for(int j = 0; j < len; j++) {
				if(board[i-1][j] == '.')
					ifs << "#";
				else
					ifs << " ";
			}
			ifs << "|" << endl;
		}
	}
	ifs << endl << "Clues: " << endl;
	ifs << "Location | Direction | Anagram" << endl;

	for(int i = 0; i < Clues.size(); i++) {

		ifs << right << setw(5) << Clues[i].r << "," << setw(2) << Clues[i].c;
		ifs << " |";
		if(Clues[i].z == 1)
			ifs << "    Across | ";
		else
			ifs << "      Down | ";

		ifs << left << Clues[i].a << endl;
	}
	for(int i = 0; i < notPlaced.size(); i++)
		cout << notPlaced[i] << " could not be placed." << endl;

	ifs.close();
}

string Board::anagram(string word) {
	// Creating an anagram for a given words. (the clue)
	srand(time(0));	
		for(int i = 0; i < (rand() % 100); i++)
			random_shuffle(word.begin(), word.end());
	return word;
}

bool Board::canPlace(int r, int c, int z, string word) {
	// Count word intersections
	int count = 0;
	// Check if a word can be placed in a given coordiante (r,c)
	// with orientation z
	// if z == 0 try horizontally
	// if z == 1 try vertically
	if(z == 0) {
		// If word woulf go out of board
		if((word.size() + c) > (len-1))
			return false;

		// Checking the word does not intersec with more than one letter of a word
		for(int i = 0; i < word.size(); i++) {
			if(board[r][c+i] == word[i])
				if(++count > 1)
					return false;
			// It may intersect with more than one word (one letter per word)
			if(board[r][c+i] == '.')
				count = 0;
			// If the board has a different letter than the word
			if((board[r][c+i] != word[i]) && (board[r][c+i] != '.'))
				return false;
		}
		// If there are letters on the surrounding areas
		// Left
		if((c - 1) >= 0)
			if(board[r][c-1] != '.')
				return false;
		// Right
		if((c + word.size()) < len)
			if(board[r][c+word.size()+1] != '.')
				return false;
		// Alongside top
		if((r - 1) >= 0)
			for(int i = 0; i < word.size(); i++)
				if(board[r-1][i+c] != '.') 
					if(board[r][i+c] != word[i])
						return false;
		// Alongside bottom
		if((r + 1) < len)
			for(int i = 0; i < word.size(); i++)
				if(board[r+1][i+c] != '.')
					if(board[r][i+c] != word[i])
						return false;
	}
	// Same logic as before exepct for vertical placement now.
	else {
		if((word.size() + r) > (len))
			return false;
		for(int i = 0; i < word.size(); i++) {
			if(board[r+i][c] == word[i])
				if(++count > 1)
					return false;
			if(board[r+i][c] == '.')
				count = 0;

			if((board[r+i][c] != word[i]) && (board[r+i][c] != '.'))
				return false;
		}
		if((r - 1) >= 0)
			if(board[r-1][c] != '.')
				return false;
		if((r + word.size()) < len)
			if(board[r+word.size()][c] != '.')
				return false;
		if((c - 1) >= 0)
			for(int i = 0; i < word.size(); i++)
				if(board[i+r][c-1] != '.')
					if(board[r+i][c] != word[i])
						return false;
		if((c + 1) < len)
			for(int i = 0; i < word.size(); i++)
				if(board[i+r][c+1] != '.')
					if(board[r+i][c] != word[i])
						return false;
	}
	return true;
}

void Board::place(int r, int c, int z, string word) {
	// Place a word on the board with the given (r,c)
	// and orientation z
	if(z == 0)
		for(int i = 0; i < word.size(); i++)
			board[r][c+i] = word[i];
	else
		for(int i = 0; i < word.size(); i++)
			board[r+i][c] = word[i];
}

vector<pair<int,int>> Board::findMatch(char letter) {
	// Finding matching char in the board
	vector<pair<int,int>> matches;
	pair<int,int> temp;

	// If a maching char is found push back the coordinate
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++)
			if(board[i][j] == letter) {
				temp.first = i;
				temp.second = j;
				matches.push_back(temp);
			}	
	return matches;
}


void Board::make() {
	// Sort biggest to smallest
	sort();

	// Placing the first word in the middle
	int temp = (len - words[0].size()) / 2;
	place((len/2),temp,0,words[0]);

	Clues.push_back({(len/2), temp, 0, anagram(words[0])});
	// Keep on placing words
	for(int i = 1; i < words.size(); i++) {
		bool placed = false;
		bool added = false;

		// Iterate through each letter in the word trying to place it
		for(int j = 0; j < words[i].size(); j++) {
			// Get all matching letter on the board
			vector<pair<int,int>> match = findMatch(words[i][j]);
			// Iterating throught all matches
			for(auto it = match.begin(); it != match.end(); it++) {
				// If it can be placed horizontally, place it and push back the clue
				if(canPlace(it->first,(it->second - j),0,words[i])) {
					place(it->first,(it->second - j),0,words[i]);
					placed = true;
					Clues.push_back({it->first, (it->second - j), 0, anagram(words[i])});
					break;
				}
				// else If it can be placed vertically, place it and push back the clue
				else if(canPlace((it->first - j),it->second,1,words[i])) {
					place((it->first - j),it->second,1,words[i]);
					placed = true;
					Clues.push_back({(it->first - j), it->second, 1, anagram(words[i])});
					break;
				}	
			}
			if(placed)
				break;
		}
		// If it couldnt be placed add it here
		if(!placed && !added)
			notPlaced.push_back(words[i]);
	}
	// After all words have been placed, try to placed unplaced words again
	int past, size;
	past = 0;
	while(true) {
		// If no new words placed from last iteration then break
		size = notPlaced.size();
		if(past == size)
			break;
		past = size;
		// Same logic as before placing words
		for(int i = 0; i < notPlaced.size(); i++) {
			bool placed = false;
			bool added = false;

			for(int j = 0; j < notPlaced[i].size(); j++) {
				vector<pair<int,int>> match = findMatch(notPlaced[i][j]);
				if(match.empty()){
					break;
				}
				for(auto it = match.begin(); it != match.end(); it++) {
					if(canPlace((it->first - j),it->second,0,words[i])) {
						place((it->first - j),it->second,0,words[i]);
						placed = true;
						Clues.push_back({it->first - j, it->second, 0, anagram(words[i])});
						notPlaced.erase	(notPlaced.begin() + i);
						break;
					}
					else if(canPlace(it->first,(it->second - j),1,words[i])) {
						place(it->first,(it->second - j),1,words[i]);
						placed = true;
						Clues.push_back({it->first - j, it->second, 1, anagram(words[i])});
						notPlaced.erase	(notPlaced.begin() + i);
						break;
					}	
				}
				if(placed)
					break;
			}
		}
	}	
}

