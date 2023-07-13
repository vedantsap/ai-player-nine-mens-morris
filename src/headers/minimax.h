#ifndef MINIMAX_H
#define MINIMAX_H

#include "constants.h"
#include "prototypes.h"

static int miniMaxPositionsEvaluated = 0;

string MiniMaxOpening(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxPositionsEvaluated = 0;
	move = MaxMin(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxOpeningBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxPositionsEvaluated = 0;
	move = MinMax(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMin(GameNode &move, int depth)
{
	if (depth == 0)
	{
		miniMaxPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpening(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MINIMUM - 1;
	vector<string> allmoves = generateMovesOpening(move.board);
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMax(nextMoveCandidateNode, depth - 1);
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMax(GameNode &move, int depth)
{
	if (depth == 0)
	{
		miniMaxPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpening(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	GameNode nextMoveCandidateNode;
	int value = STATIC_ESTIMATE_MAXIMUM + 1;
	vector<string> allmoves = generateMovesOpening(invertBoard(move.board));
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMin(nextMoveCandidateNode, depth - 1);
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

string MiniMaxGame(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxPositionsEvaluated = 0;
	move = MaxMinGame(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxGameBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move.staticEstimate = 0;
	miniMaxPositionsEvaluated = 0;
	move = MinMaxGame(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << miniMaxPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMinGame(GameNode &move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		miniMaxPositionsEvaluated++;
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
		GameNode minMax = MinMaxGame(nextMoveCandidateNode, depth - 1);
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMaxGame(GameNode &move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		miniMaxPositionsEvaluated++;
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
		GameNode maxMin = MaxMinGame(nextMoveCandidateNode, depth - 1);
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