#ifndef BOARD_H
#define BOARD_H

#include "prototypes.h"
#include "constants.h"

void printBoard(string board)
{
	replace(board.begin(), board.end(), EMPTY_POSITION, '.');
	cout << endl;
	cout << "          " << board[18]
		 << " - - "
		 << board[19]
		 << " - - "
		 << board[20] << endl;
	cout << "          "
		 << "| "
		 << board[15]
		 << " - "
		 << board[16]
		 << " - "
		 << board[17]
		 << " |" << endl;
	cout << "          "
		 << "| | "
		 << board[12]
		 << " "
		 << board[13]
		 << " "
		 << board[14]
		 << " | |" << endl;
	cout << "          " << board[6]
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
	cout << "          "
		 << "| | "
		 << board[4]
		 << " - "
		 << board[5]
		 << " | |" << endl;
	cout << "          "
		 << "| "
		 << board[2]
		 << " - - - "
		 << board[3]
		 << " |" << endl;
	cout << "          " << board[0]
		 << " - - - - - "
		 << board[1] << endl;
	cout << endl;
	return;
}

void printDelta(const string &oldBoard, const string &newBoard)
{
	cout << endl;
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
	return count(board.begin(), board.end(), piece);
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

bool isWinner(const string &board)
{
	vector<string> blackMoves = generateMovesMidgameEndgame(invertBoard(board));
	return blackMoves.size() == 0 || countPieces(board, BLACK_PIECE) <= 2;
}

#endif