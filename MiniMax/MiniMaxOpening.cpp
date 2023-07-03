#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
using namespace std;

// Define constants to be used across the program
const char EMPTY_POSITION = 'x';
const char WHITE_PIECE = 'W';
const char BLACK_PIECE = 'B';
const int BOARD_SIZE = 21;
const string EMPTY_BOARD = "xxxxxxxxxxxxxxxxxxxxx";

const int STATIC_ESTIMATE_MINIMUM = -10000;
const int STATIC_ESTIMATE_MAXIMUM = 10000;
const int STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER = 1000;



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

/**
 * Mapping to store value of mills possible at each board position
 * key: position on board
 * value: mills that can be made with this position
 */
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

// METHOD PROTOTYPES
// 1. board position and file handling utilities

string readFile(string fileName);
void printBoard(string board);
void printDelta(const string &oldBoard, const string &newBoard);

// 2. abstracted position generators

vector<string> generateMovesOpening(const string &board);
vector<string> generateMovesMidgameEndgame(const string &board);

// 3. position generators

vector<string> generateAdd(const string &board);
vector<string> generateMove(const string &board);
vector<string> generateHopping(const string &board);
void generateRemove(const string &board, vector<string> &positions);

// 6. Static estimation functions

int staticEstimationOpening(const string &board);
int staticEstimationMidgameEndgame(const string &board);

// 5. utils and adapters for position generators

bool closeMill(int position, const string &board);
int countPieces(const string &board, const char &piece);
string invertBoard(string board);

string readFile(string fileName)
{
	ifstream boardPositionFile(fileName);
	if (!boardPositionFile)
	{
		throw runtime_error("invalid file");
	}
	string boardPosition;
	boardPositionFile >> boardPosition;
	if (boardPosition.size() != BOARD_SIZE)
	{
		throw runtime_error("invalid board position within file");
	}
	boardPositionFile.close();
	return boardPosition;
}

void printBoard(string board)
{
	replace(board.begin(), board.end(), EMPTY_POSITION, '.');
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

void printDelta(const string &oldBoard, const string &newBoard)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (oldBoard[i] != newBoard[i] && oldBoard[i] == EMPTY_POSITION)
		{
			if (newBoard[i] == WHITE_PIECE)
				cout << "WHITE added to " << i << endl;
			if (newBoard[i] == BLACK_PIECE)
				cout << "BLACK added to " << i << endl;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (oldBoard[i] != newBoard[i] && newBoard[i] == EMPTY_POSITION)
		{
			if (oldBoard[i] == WHITE_PIECE)
				cout << "WHITE removed from " << i << endl;
			if (oldBoard[i] == BLACK_PIECE)
				cout << "BLACK removed from " << i << endl;
		}
	}
	cout << endl;
}

// TODO Black Move generator adapter

/**
 * Generates moves during the opening phase of game
 * Adds pieces to the board
 * @param board: starting board on which a white piece needs to make a move
 * @return a list of valid board positions after adding
 *
 */
vector<string> generateMovesOpening(const string &board)
{
	return generateAdd(board);
}

/**
 * Generates moves during the midgame and endgame phase of game
 * Moves and hops pieces around on the board
 * @param board: starting board on which a white piece needs to make a move
 * @return a list of valid board positions after moving or hopping
 */
vector<string> generateMovesMidgameEndgame(const string &board)
{
	if (countPieces(board, WHITE_PIECE) == 3)
	{
		return generateHopping(board);
	}
	else
	{
		return generateMove(board);
	}
}

/**
 * Generates possible ADD moves on the board
 * Plays WHITE by default
 */
vector<string> generateAdd(const string &board)
{
	vector<string> positions;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == EMPTY_POSITION)
		{
			string generatedBoard = board; // copy const into a new string
			generatedBoard[i] = WHITE_PIECE;
			if (closeMill(i, generatedBoard))
			{
				generateRemove(generatedBoard, positions);
			}
			else
			{
				positions.push_back(generatedBoard);
			}
		}
	}
	return positions;
}

vector<string> generateMove(const string &board)
{
	vector<string> positions;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == WHITE_PIECE)
		{
			for (int j : neighbors.at(i))
			{
				if (board[j] == EMPTY_POSITION)
				{
					string generatedBoard = board;
					generatedBoard[i] = EMPTY_POSITION;
					generatedBoard[j] = WHITE_PIECE;
					if (closeMill(j, generatedBoard))
					{
						generateRemove(generatedBoard, positions);
					}
					else
					{
						positions.push_back(generatedBoard);
					}
				}
			}
		}
	}
	return positions;
}

vector<string> generateHopping(const string &board)
{
	vector<string> positions;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == WHITE_PIECE)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[j] == EMPTY_POSITION)
				{
					string generatedBoard = board;
					generatedBoard[i] = EMPTY_POSITION;
					generatedBoard[j] = WHITE_PIECE;
					if (closeMill(j, generatedBoard))
					{
						generateRemove(generatedBoard, positions);
					}
					else
					{
						positions.push_back(generatedBoard);
					}
				}
			}
		}
	}
	return positions;
}

/**
 * Removes one BLACK piece from the board, called when a WHITE mill is created
 * @param board: board position
 * @param moves: list of moves being generated from the method above
 */
void generateRemove(const string &board, vector<string> &moves)
{
	bool blackPiecesRemoved = false;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == BLACK_PIECE)
		{
			if (!closeMill(i, board))
			{
				string generatedBoard = board;
				generatedBoard[i] = EMPTY_POSITION;
				moves.push_back(generatedBoard);
			}
		}
	}
	// If no black pieces could removed (all were within mills) and continue with the same board
	if (!blackPiecesRemoved)
	{
		moves.push_back(board);
	}
}

int staticEstimationOpening(const string &board)
{
	return countPieces(board, WHITE_PIECE) - countPieces(board, BLACK_PIECE);
}

int staticEstimationMidgameEndgame(const string &board)
{
	int numBlackPieces = countPieces(board, BLACK_PIECE);
	if(numBlackPieces <= 2)
	{
		return STATIC_ESTIMATE_MAXIMUM;
	}
	int numWhitePieces = countPieces(board, WHITE_PIECE);
	if(numWhitePieces <= 2)
	{
		return STATIC_ESTIMATE_MINIMUM;
	}
	vector<string> blackMoves = generateMovesMidgameEndgame(invertBoard(board));
	if(blackMoves.size()==0)
	{
		return STATIC_ESTIMATE_MAXIMUM;
	}
	return STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER * (numWhitePieces - numBlackPieces) - blackMoves.size(); 
}

/**
 * 1. When WHITE at position, checks if adding WHITE at position created mill(s)
 * 2. When BLACK at position, checks if a BLACK piece can be removed from this position
 */
bool closeMill(int position, const string &board)
{
	vector<vector<int>> possibleMills = mills.at(position);
	char piece = board[position];
	for (vector<int> mill : possibleMills)
	{
		if (board[mill[0]] == piece && board[mill[1]] == piece && board[mill[2]] == piece)
		{
			return true;
		}
	}
	return false;
}

int countPieces(const string &board, const char &piece)
{
	int count = 0;
	for (const char &position : board)
	{
		if (position == piece)
			count++;
	}
	return count;
}

string invertBoard(string board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == WHITE_PIECE)
			board[i] = BLACK_PIECE;
		else if (board[i] == BLACK_PIECE)
			board[i] = WHITE_PIECE;
	}
	return board;
}

void playAiVsAi(string startPosition)
{
	cout << "Starting game AI vs AI. WHITE to play first!" << endl;
	int round = 0;
	for (int i = 0; i < 8; i++)
	{
		vector<string> whiteMoves = generateAdd(startPosition);
		string newPosition = whiteMoves[rand() % whiteMoves.size()];
		cout << "**************************************************Round: " << 2 * i + 1 << endl;
		cout << "WHITE played:" << endl;
		printDelta(startPosition, newPosition);
		printBoard(newPosition);

		string invertedBoard = invertBoard(newPosition);
		vector<string> blackMovesInverted = generateAdd(invertedBoard);
		string startPositionInverted = blackMovesInverted[rand() % blackMovesInverted.size()];
		startPosition = invertBoard(startPositionInverted);
		cout << "**************************************************Round: " << 2 * i + 2 << endl;
		cout << "BLACK played:" << endl;
		printDelta(newPosition, startPosition);
		printBoard(startPosition);
	}
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
	playAiVsAi(EMPTY_BOARD);
}