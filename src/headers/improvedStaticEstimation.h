#ifndef IMPROVEDSTATICESTIMATION_H
#define IMPROVEDSTATICESTIMATION_H

#include "prototypes.h"
#include "constants.h"

int staticEstimationOpeningImproved(const string &board)
{
	vector<string> blackMoves = generateMovesMidgameEndgame(invertBoard(board));
	if (blackMoves.size() == 0)
	{
		return STATIC_ESTIMATE_MAXIMUM;
	}
	vector<string> whiteMoves = generateMovesMidgameEndgame(board);
	if (whiteMoves.size() == 0)
	{
		return STATIC_ESTIMATE_MINIMUM;
	}

	// 1. Reward having more pieces than BLACK
	int staticEstimate = IMPROVED_STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER * (countPieces(board, WHITE_PIECE) - countPieces(board, BLACK_PIECE));

	// 2. Reward completing half mills
	// staticEstimate += 250 * totalHalfMills(board);

	// 3. Reward number of empty neighbors a piece has
	staticEstimate += 100 * getEmptyNeighbors(board);
	return staticEstimate;
}

int getEmptyNeighbors(const string &board)
{
	int emptyNeighbors = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (board[i] == WHITE_PIECE)
		{
			vector<int> neighboringPositions = neighbors.at(i);
			for (int neigh : neighboringPositions)
			{
				if (board[neigh] == EMPTY_POSITION)
					emptyNeighbors++;
			}
		}
	}
	return emptyNeighbors;
}

// int totalHalfMills(const string &board)
// {
// 	int total = 0;
// 	for (int i = 0; i < BOARD_SIZE; i++)
// 	{
// 		if (board[i] == WHITE_PIECE)
// 		{
// 			vector<vector<int>> possibleMills = mills.at(i);
// 			for (vector<int> mill : possibleMills)
// 			{
// 				if ((board[mill[0]] == WHITE_PIECE && board[mill[1]] == WHITE_PIECE) || (board[mill[1]] == WHITE_PIECE && board[mill[2]] == WHITE_PIECE) || (board[mill[2]] == WHITE_PIECE && board[mill[0]] == WHITE_PIECE))
// 				{
// 					total++;
// 				}
// 			}
// 		}
// 	}
// 	return total;
// }

int staticEstimationMidgameEndgameImproved(const string &board)
{
	int numBlackPieces = countPieces(board, BLACK_PIECE);
	if (numBlackPieces <= 2)
	{
		return STATIC_ESTIMATE_MAXIMUM;
	}
	int numWhitePieces = countPieces(board, WHITE_PIECE);
	if (numWhitePieces <= 2)
	{
		return STATIC_ESTIMATE_MINIMUM;
	}
	vector<string> blackMoves = generateMovesMidgameEndgame(invertBoard(board));
	if (blackMoves.size() == 0)
	{
		return STATIC_ESTIMATE_MAXIMUM;
	}
	vector<string> whiteMoves = generateMovesMidgameEndgame(board);
	if (whiteMoves.size() == 0)
	{
		return STATIC_ESTIMATE_MINIMUM;
	}
	int staticEstimate = STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER * (numWhitePieces - numBlackPieces) - blackMoves.size() + whiteMoves.size();
	// staticEstimate += 100 * totalHalfMills(board);
	return staticEstimate;
}

#endif