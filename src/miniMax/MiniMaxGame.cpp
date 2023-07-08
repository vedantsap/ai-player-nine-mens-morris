#include "../headers/fileIO.h"
#include "../headers/staticEstimators.h"
#include "../headers/generator.h"

using namespace std;

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

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "There should be only 4 parameters! Example : MiniMaxGame.exe board1.txt board2.txt 2" << endl;
		return -1;
	}
	string currentPosition = readFile(argv[1]);
	cout << "Board as string: " << currentPosition << endl;
	printBoard(currentPosition);
	string newPosition = MiniMaxGame(currentPosition, 2);
	printDelta(currentPosition, newPosition);
	printBoard(newPosition);
	writeFile("board2.txt", newPosition);
}