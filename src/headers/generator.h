#ifndef GENERATOR_H
#define GENERATOR_H

#include "constants.h"
#include "board.h"

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
	int count = countPieces(board, WHITE_PIECE);
	if (count < 3)
		return {};
	if (count == 3)
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
		if (board[i] == BLACK_PIECE && !closeMill(i, board))
		{
			blackPiecesRemoved = true;
			string generatedBoard = board;
			generatedBoard[i] = EMPTY_POSITION;
			moves.push_back(generatedBoard);
		}
	}
	// If no black pieces could removed (all were within mills) and continue with the same board
	if (!blackPiecesRemoved)
	{
		moves.push_back(board);
	}
}

#endif