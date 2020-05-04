// Class definitions
// By: Jorge Daboub

using namespace std;
const int len = 15;

class Board {

	public:
		Board();
		~Board();
		void display();
		void addWord(string);
		void sort();
		void readIn();
		void readInFile(string);
		void toFile(string);
		string anagram(string a);
		bool canPlace(int,int,int,string);
		void place(int,int,int,string);
		vector<pair<int,int>> findMatch(char);
		void make();

	private:
		vector<string> words;
		bool output;
		string fileName;
		char board[len][len];
		struct Clue
		{
			int r, c, z;
			string a;
		};
		vector<Clue> Clues;
		vector<string> notPlaced;	
};
