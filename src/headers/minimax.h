#ifndef MINIMAX_H
#define MINIMAX_H

#include "constants.h"
#include "prototypes.h"

// Global variable to keep count of positions evaluated
int numberOfPositionsEvaluated = 0;

string MiniMaxOpening(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	numberOfPositionsEvaluated = 0;
	move = MaxMin(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << numberOfPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxOpeningBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	numberOfPositionsEvaluated = 0;
	move = MinMax(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << numberOfPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMin(GameNode move, int depth)
{
	if (depth == 0)
	{
		numberOfPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpening(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MIN;
	GameNode nextMoveCandidateNode;
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
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMax(GameNode move, int depth)
{
	if (depth == 0)
	{
		numberOfPositionsEvaluated++;
		move.staticEstimate = staticEstimationOpening(move.board);
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MAX;
	GameNode nextMoveCandidateNode;
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
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	return nextMoveBestNode;
}

//////////////////////// maybe separate the below into another .h file

string MiniMaxGame(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	numberOfPositionsEvaluated = 0;
	move = MaxMinGame(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << numberOfPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

string MiniMaxGameBlack(const string &board, int depth)
{
	GameNode move;
	move.board = board;
	numberOfPositionsEvaluated = 0;
	move = MinMaxGame(move, depth);

	cout << "### Board Position: " << move.board << endl;
	cout << "### Positions evaluated by static estimation: " << numberOfPositionsEvaluated << endl;
	cout << "### MINIMAX estimate: " << move.staticEstimate << endl;

	return move.board;
}

GameNode MaxMinGame(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		numberOfPositionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MIN;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesMidgameEndgame(move.board);
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = nextMove;
		GameNode minMax = MinMaxGame(nextMoveCandidateNode, depth - 1);
		if (value < minMax.staticEstimate)
		{
			value = minMax.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	return nextMoveBestNode;
}

GameNode MinMaxGame(GameNode move, int depth)
{
	if (depth == 0)
	{
		move.staticEstimate = staticEstimationMidgameEndgame(move.board);
		numberOfPositionsEvaluated++;
		return move;
	}
	GameNode nextMoveBestNode;
	int value = INT_MAX;
	GameNode nextMoveCandidateNode;
	vector<string> allmoves = generateMovesMidgameEndgame(invertBoard(move.board));
	for (const string &nextMove : allmoves)
	{
		nextMoveCandidateNode.board = invertBoard(nextMove);
		GameNode maxMin = MaxMinGame(nextMoveCandidateNode, depth - 1);
		if (value > maxMin.staticEstimate)
		{
			value = maxMin.staticEstimate;
			nextMoveBestNode.board = nextMoveCandidateNode.board;
			nextMoveBestNode.staticEstimate = value;
			// nextMoveBestNode.next = &nextMoveCandidateNode;
		}
	}
	return nextMoveBestNode;
}

#endif