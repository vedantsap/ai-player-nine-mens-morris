#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

// Define constants to be used across the program
const char EMPTY_POSITION = 'x';
const char WHITE_PIECE = 'W';
const char BLACK_PIECE = 'B';

// Mapping to store neighbors of positions as an adjacency list
const unordered_map<int, vector<int>> neighbors = {
	{0, {1, 6}},
	{1, {0, 11}},
	{2, {3, 7}},
	{3, {2, 10}},
	{4, {5, 8}},
	{5, {4, 9}},
	{6, {0, 7, 18}},
	{7, {2, 6, 8, 15}},
	{8, {4, 7, 12}},
	{9, {5, 10, 14}},
	{10, {3, 9, 11, 17}},
	{11, {1, 10, 20}},
	{12, {8, 13}},
	{13, {12, 14, 16}},
	{14, {9, 13}},
	{15, {7, 16}},
	{16, {13, 15, 17, 19}},
	{17, {10, 16}},
	{18, {6, 19}},
	{19, {16, 18, 20}},
	{20, {1, 19}}};

// Mapping to store value of mills possible at each board position
const unordered_map<int, vector<vector<int>>> mills = {
	{0, {{0, 6, 18}}},
	{1, {{1, 11, 20}}},
	{2, {{2, 7, 15}}},
	{3, {{3, 10, 17}}},
	{4, {{4, 8, 12}}},
	{5, {{5, 9, 14}}},
	{6, {{6, 7, 8}, {0, 6, 18}}},
	{7, {{6, 7, 8}, {2, 7, 15}}},
	{8, {{6, 7, 8}, {4, 8, 12}}},
	{9, {{9, 10, 11}, {5, 9, 14}}},
	{10, {{9, 10, 11}, {3, 10, 17}}},
	{11, {{9, 10, 11}, {1, 11, 20}}},
	{12, {{12, 13, 14}, {4, 8, 12}}},
	{13, {{12, 13, 14}, {13, 16, 19}}},
	{14, {{12, 13, 14}, {5, 9, 14}}},
	{15, {{15, 16, 17}, {2, 7, 15}}},
	{16, {{15, 16, 17}, {13, 16, 19}}},
	{17, {{15, 16, 17}, {3, 10, 17}}},
	{18, {{18, 19, 20}, {0, 6, 18}}},
	{19, {{18, 19, 20}, {13, 16, 19}}},
	{20, {{18, 19, 20}, {1, 11, 20}}},
};

// Define method prototypes
string readFile(string fileName);
void printBoard(string board);
vector<string> generateAdd(const string &board);
string generateMove(string board);
string generateAHopping(string board);
string generateRemove(string board);

string readFile(string fileName)
{
	ifstream boardPositionFile(fileName);
	if (!boardPositionFile)
	{
		throw runtime_error("invalid file");
	}
	string boardPosition;
	boardPositionFile >> boardPosition;
	if (boardPosition.size() != 21)
	{
		throw runtime_error("invalid board position within file");
	}
	boardPositionFile.close();
	return boardPosition;
}

void printBoard(string board)
{
	replace(board.begin(), board.end(), EMPTY_POSITION, '.');
	cout << endl;
	cout << board[18]
		 << " - - "
		 << board[19]
		 << " - - "
		 << board[20] << endl;
	cout << "| "
		 << board[15]
		 << " - "
		 << board[16]
		 << " - "
		 << board[17]
		 << " |" << endl;
	cout << "| | "
		 << board[12]
		 << " "
		 << board[13]
		 << " "
		 << board[14]
		 << " | |" << endl;
	cout << board[6]
		 << " "
		 << board[7]
		 << " "
		 << board[8]
		 << "   "
		 << board[9]
		 << " "
		 << board[10]
		 << " "
		 << board[11] << endl;
	cout << "| | "
		 << board[4]
		 << " - "
		 << board[5]
		 << " | |" << endl;
	cout << "| "
		 << board[2]
		 << " - - - "
		 << board[3]
		 << " |" << endl;
	cout << board[0]
		 << " - - - - - "
		 << board[1] << endl;
	return;
}

// TODO Black Move generator adapter

/**
 * Generates possible ADD moves on the board
 * Plays WHITE by default
 */
vector<string> generateAdd(const string &board)
{
	vector<string> positions;
	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == EMPTY_POSITION)
		{
			string generatedBoard = board; // copy const into a new string
			generatedBoard[i] = WHITE_PIECE;
			positions.push_back(board);
		}
	}
	return positions;
}

string generateMove(string board)
{
}

string generateAHopping(string board)
{
}

string generateRemove(string board)
{
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "there should be only 1 parameter" << endl;
		return -1;
	}
	string currentPosition = readFile(argv[1]);
	cout << "Board as string: " << currentPosition << endl;
	printBoard(currentPosition);
}