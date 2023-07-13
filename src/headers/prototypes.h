#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "constants.h"

// METHOD PROTOTYPES
// 1. board position and file handling utilities

string readFile(string fileName);
void writeFile(string fileName, string board);
void printBoard(string board);
void printDelta(const string &oldBoard, const string &newBoard);

// 2. abstracted position generators

vector<string> generateMovesOpening(const string &board);
vector<string> generateMovesMidgameEndgame(const string &board);

// 3. position generators

vector<string> generateAdd(const string &board);
vector<string> generateMove(const string &board);
vector<string> generateHopping(const string &board);
void generateRemove(const string &board, vector<string> &positions);

// 4. Static estimation functions

int staticEstimationOpening(const string &board);
int staticEstimationMidgameEndgame(const string &board);
int staticEstimationOpeningImproved(const string &board);
int staticEstimationMidgameEndgameImproved(const string &board);

// 4.5 IMPROVED static estimation functions
int getEmptyNeighbors(const string &board);
int totalHalfMills(const string &board);
int staticEstimationOpeningImproved(const string &board);
int staticEstimationMidgameEndgameImproved(const string &board);

// 5. utils and adapters for position generators

bool closeMill(int position, const string &board);
int countPieces(const string &board, const char &piece);
string invertBoard(string board);
bool isWinner(const string &board);

// 6. MiniMax algorithm functions

string MiniMaxOpening(const string &board, int depth);
string MiniMaxOpeningBlack(const string &board, int depth);
GameNode MaxMin(GameNode &move, int depth);
GameNode MinMax(GameNode &move, int depth);

string AlphaBetaOpening(const string &board, int depth);
string AlphaBetaOpeningBlack(const string &board, int depth);
GameNode MaxMin(GameNode &move, int alpha, int beta, int depth);
GameNode MinMax(GameNode &move, int alpha, int beta, int depth);

string MiniMaxGame(const string &board, int depth);
string MiniMaxGameBlack(const string &board, int depth);
GameNode MaxMinGame(GameNode &move, int depth);
GameNode MinMaxGame(GameNode &move, int depth);

string AlphaBetaGame(const string &board, int depth);
string AlphaBetaGameBlack(const string &board, int depth);
GameNode MaxMinGame(GameNode &move, int alpha, int beta, int depth);
GameNode MinMaxGame(GameNode &move, int alpha, int beta, int depth);

// 7. MiniMax Improved
string MiniMaxOpeningImproved(const string &board, int depth);
string MiniMaxOpeningImprovedBlack(const string &board, int depth);
GameNode MaxMinImproved(GameNode &move, int depth);
GameNode MinMaxImproved(GameNode &move, int depth);
string MiniMaxGameImproved(const string &board, int depth);
string MiniMaxGameImprovedBlack(const string &board, int depth);
GameNode MaxMinGameImproved(GameNode &move, int depth);
GameNode MinMaxGameImproved(GameNode &move, int depth);

#endif