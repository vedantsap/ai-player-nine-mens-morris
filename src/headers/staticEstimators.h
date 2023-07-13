#ifndef STATICESTIMATORS_H
#define STATICESTIMATORS_H

#include "prototypes.h"
#include "constants.h"

int staticEstimationOpening(const string &board)
{
	return countPieces(board, WHITE_PIECE) - countPieces(board, BLACK_PIECE);
}

int staticEstimationMidgameEndgame(const string &board)
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
	// vector<string> whitekMoves = generateMovesMidgameEndgame(board);
	// if (whitekMoves.size() == 0)
	// {
	// 	return STATIC_ESTIMATE_MINIMUM;
	// }
	return STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER * (numWhitePieces - numBlackPieces) - blackMoves.size();
}

#endif