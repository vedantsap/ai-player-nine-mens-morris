#ifndef MINIMAXIMPROVED_H
#define MINIMAXIMPROVED_H

#include "constants.h"
#include "prototypes.h"
#include "improvedStaticEstimation.h"

static int miniMaxImprovedPositionsEvaluated = 0;

string MiniMaxOpeningImproved(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxImprovedPositionsEvaluated = 0;
	move = MaxMinImproved(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxImprovedPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxOpeningImprovedBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxImprovedPositionsEvaluated = 0;
	move = MinMaxImproved(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxImprovedPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMinImproved(GameNode &move, int depth)
{
	if (depth == 0)
	{
		miniMaxImprovedPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpeningImproved(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MINIMUM - 1;
	vector<string> allmoves = generateMovesOpening(move.board);
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMaxImproved(nextMoveCandidateNode, depth - 1);
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMaxImproved(GameNode &move, int depth)
{
	if (depth == 0)
	{
		miniMaxImprovedPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpeningImproved(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MAXIMUM + 1;
	vector<string> allmoves = generateMovesOpening(invertBoard(move.board));
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMinImproved(nextMoveCandidateNode, depth - 1);
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

string MiniMaxGameImproved(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxImprovedPositionsEvaluated = 0;
	move = MaxMinGameImproved(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxImprovedPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxGameImprovedBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxImprovedPositionsEvaluated = 0;
	move = MinMaxGameImproved(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxImprovedPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMinGameImproved(GameNode &move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgameImproved(move.board);
		miniMaxImprovedPositionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MINIMUM - 1;
	vector<string> allmoves = generateMovesMidgameEndgame(move.board);
	if (allmoves.size() == 0)
	{
		move.staticEstimate = value;
		return move;
	}
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMaxGameImproved(nextMoveCandidateNode, depth - 1);
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMaxGameImproved(GameNode &move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgameImproved(move.board);
		miniMaxImprovedPositionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MAXIMUM + 1;
	vector<string> allmoves = generateMovesMidgameEndgame(invertBoard(move.board));
	if (allmoves.size() == 0)
	{
		move.staticEstimate = value;
		return move;
	}
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMinGameImproved(nextMoveCandidateNode, depth - 1);
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

#endif