#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "constants.h"
#include "prototypes.h"

// Singleton global variable to keep count of positions evaluated
static int alphaBetaPositionsEvaluated = 0;

string AlphaBetaOpening(const string &board, int depth)
{
    GameNode move;
    move.board = board;
    move.staticEstimate = 0;
    alphaBetaPositionsEvaluated = 0;
    move = MaxMin(move, STATIC_ESTIMATE_MINIMUM, STATIC_ESTIMATE_MAXIMUM, depth);

    cout << "### Board Position: " << move.board << endl;
    cout << "### Positions evaluated by static estimation: " << alphaBetaPositionsEvaluated << endl;
    cout << "### ALPHA-BETA estimate: " << move.staticEstimate << endl;

    return move.board;
}

string AlphaBetaOpeningBlack(const string &board, int depth)
{
    GameNode move;
    move.board = board;
    move.staticEstimate = 0;
    alphaBetaPositionsEvaluated = 0;
    move = MinMax(move, STATIC_ESTIMATE_MINIMUM, STATIC_ESTIMATE_MAXIMUM, depth);

    cout << "### Board Position: " << move.board << endl;
    cout << "### Positions evaluated by static estimation: " << alphaBetaPositionsEvaluated << endl;
    cout << "### ALPHA-BETA estimate: " << move.staticEstimate << endl;

    return move.board;
}

GameNode MaxMin(GameNode &move, int alpha, int beta, int depth)
{
    if (depth == 0)
    {
        alphaBetaPositionsEvaluated++;
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
        GameNode minMax = MinMax(nextMoveCandidateNode, alpha, beta, depth - 1);
        if (value < minMax.staticEstimate)
        {
            value = minMax.staticEstimate;
            nextMoveBestNode.board = nextMoveCandidateNode.board;
            nextMoveBestNode.staticEstimate = value;
            if (value >= beta)
            {
                return nextMoveBestNode;
            }
            else
            {
                alpha = max(value, alpha);
            }
        }
    }
    return nextMoveBestNode;
}

GameNode MinMax(GameNode &move, int alpha, int beta, int depth)
{
    if (depth == 0)
    {
        alphaBetaPositionsEvaluated++;
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
        GameNode maxMin = MaxMin(nextMoveCandidateNode, alpha, beta, depth - 1);
        if (value > maxMin.staticEstimate)
        {
            value = maxMin.staticEstimate;
            nextMoveBestNode.board = nextMoveCandidateNode.board;
            nextMoveBestNode.staticEstimate = value;
            if (value <= alpha)
            {
                return nextMoveBestNode;
            }
            else
            {
                beta = min(value, beta);
            }
        }
    }
    return nextMoveBestNode;
}

string AlphaBetaGame(const string &board, int depth)
{
    GameNode move;
    move.board = board;
    move.staticEstimate = 0;
    alphaBetaPositionsEvaluated = 0;
    move = MaxMinGame(move, STATIC_ESTIMATE_MINIMUM, STATIC_ESTIMATE_MAXIMUM, depth);

    cout << "### Board Position: " << move.board << endl;
    cout << "### Positions evaluated by static estimation: " << alphaBetaPositionsEvaluated << endl;
    cout << "### ALPHA-BETA estimate: " << move.staticEstimate << endl;

    return move.board;
}

string AlphaBetaGameBlack(const string &board, int depth)
{
    GameNode move;
    move.board = board;
    move.staticEstimate = 0;
    alphaBetaPositionsEvaluated = 0;
    move = MinMaxGame(move, STATIC_ESTIMATE_MINIMUM, STATIC_ESTIMATE_MAXIMUM, depth);

    cout << "### Board Position: " << move.board << endl;
    cout << "### Positions evaluated by static estimation: " << alphaBetaPositionsEvaluated << endl;
    cout << "### ALPHA-BETA estimate: " << move.staticEstimate << endl;

    return move.board;
}

GameNode MaxMinGame(GameNode &move, int alpha, int beta, int depth)
{
    if (depth == 0)
    {
        alphaBetaPositionsEvaluated++;
        move.staticEstimate = staticEstimationMidgameEndgame(move.board);
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
        GameNode minMax = MinMaxGame(nextMoveCandidateNode, alpha, beta, depth - 1);
        if (value < minMax.staticEstimate)
        {
            value = minMax.staticEstimate;
            nextMoveBestNode.board = nextMoveCandidateNode.board;
            nextMoveBestNode.staticEstimate = value;
            if (value >= beta)
            {
                return nextMoveBestNode;
            }
            else
            {
                alpha = max(value, alpha);
            }
        }
    }
    return nextMoveBestNode;
}

GameNode MinMaxGame(GameNode &move, int alpha, int beta, int depth)
{
    if (depth == 0)
    {
        move.staticEstimate = staticEstimationMidgameEndgame(move.board);
        alphaBetaPositionsEvaluated++;
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
        GameNode maxMin = MaxMinGame(nextMoveCandidateNode, alpha, beta, depth - 1);
        if (value > maxMin.staticEstimate)
        {
            value = maxMin.staticEstimate;
            nextMoveBestNode.board = nextMoveCandidateNode.board;
            nextMoveBestNode.staticEstimate = value;
            if (value <= alpha)
            {
                return nextMoveBestNode;
            }
            else
            {
                beta = min(value, beta);
            }
        }
    }
    return nextMoveBestNode;
}

#endif