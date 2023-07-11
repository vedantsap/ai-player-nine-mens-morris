#ifndef IMPROVEDSTATICESTIMATIONH
#define IMPROVEDSTATICESTIMATIONH

#include "prototypes.h"
#include "constants.h"

int improvedStaticEstimationOpening(const string &board)
{
	// TODO: enable memoization
	// if(STATIC_ESTIMATE_CACHE[board]==0)
	// {
	// 	STATIC_ESTIMATE_CACHE[board] = countPieces(board, WHITE_PIECE) - countPieces(board, BLACK_PIECE);
	// }
	// return STATIC_ESTIMATE_CACHE[board];
	int plainStaticEstimate = countPieces(board, WHITE_PIECE) - countPieces(board, BLACK_PIECE);
    int halfMillScore = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        if(board[i]==WHITE_PIECE) halfMillScore += halfOuterMills.at(i).size();
    }
    return 100 * plainStaticEstimate + 10 * halfMillScore;
}

int improvedStaticEstimationMidgameEndgame(const string &board)
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
	return STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER * (numWhitePieces - numBlackPieces) - blackMoves.size();
}

#endif