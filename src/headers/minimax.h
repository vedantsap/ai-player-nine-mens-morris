#ifndef MINIMAX_H
#define MINIMAX_H

#include "constants.h"
#include "prototypes.h"

string MiniMaxOpening(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move = MaxMin(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << move.positionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMin(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationOpening(move.board);
		move.positionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MIN;
	int eval = 0;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesOpening(move.board);
	for (const string &nextMove : allmoves)
	{
		eval++;
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMax(nextMoveCandidateNode, depth - 1);
		nextMoveCandidateNode.positionsEvaluated += minMax.positionsEvaluated;
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	nextMoveBestNode.positionsEvaluated += eval;
	return nextMoveBestNode;
}

GameNode MinMax(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationOpening(move.board);
		move.positionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MAX;
	int eval = 0;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesOpening(invertBoard(move.board));
	for (const string &nextMove : allmoves)
	{
		eval++;
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMin(nextMoveCandidateNode, depth - 1);
		nextMoveCandidateNode.positionsEvaluated += maxMin.positionsEvaluated;
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	nextMoveBestNode.positionsEvaluated += eval;
	return nextMoveBestNode;
}

string MiniMaxGame(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	move = MaxMinGame(move, depth);

	// TODO this prints inverted board when playing for BLACK
	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << move.positionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMinGame(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		move.positionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MIN;
	int eval = 0;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesMidgameEndgame(move.board);
	for (const string &nextMove : allmoves)
	{
		eval++;
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMaxGame(nextMoveCandidateNode, depth - 1);
		nextMoveCandidateNode.positionsEvaluated += minMax.positionsEvaluated;
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	nextMoveBestNode.positionsEvaluated += eval;
	return nextMoveBestNode;
}

GameNode MinMaxGame(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		move.positionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MAX;
	int eval = 0;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesMidgameEndgame(invertBoard(move.board));
	for (const string &nextMove : allmoves)
	{
		eval++;
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMinGame(nextMoveCandidateNode, depth - 1);
		nextMoveCandidateNode.positionsEvaluated += maxMin.positionsEvaluated;
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	nextMoveBestNode.positionsEvaluated += eval;
	return nextMoveBestNode;
}

#endif