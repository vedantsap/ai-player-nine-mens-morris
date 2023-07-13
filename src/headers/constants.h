#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
#include <limits.h>
using namespace std;

const char EMPTY_POSITION = 'x';
const char WHITE_PIECE = 'W';
const char BLACK_PIECE = 'B';
const int BOARD_SIZE = 21;
const string EMPTY_BOARD = "xxxxxxxxxxxxxxxxxxxxx";

const int STATIC_ESTIMATE_MINIMUM = -10000;
const int STATIC_ESTIMATE_MAXIMUM = 10000;
const int STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER = 1000;

const int IMPROVED_STATIC_ESTIMATE_MINIMUM = -10000;
const int IMPROVED_STATIC_ESTIMATE_MAXIMUM = 10000;
const int IMPROVED_STATIC_ESTIMATE_MIDGAME_ENDGAME_MULTIPLIER = 1000;

struct GameNode
{
	string board;
	int staticEstimate = 0;
};

// Mapping to store neighbors of positions as an adjacency list
const unordered_map<int, vector<int>> neighbors = {
	{0, {1, 6}},
	{1, {0, 11}},
	{2, {3, 7}},
	{3, {2, 10}},
	{4, {5, 8}},
	{5, {4, 9}},
	{6, {0, 7, 18}},
	{7, {2, 6, 8, 15}},
	{8, {4, 7, 12}},
	{9, {5, 10, 14}},
	{10, {3, 9, 11, 17}},
	{11, {1, 10, 20}},
	{12, {8, 13}},
	{13, {12, 14, 16}},
	{14, {9, 13}},
	{15, {7, 16}},
	{16, {13, 15, 17, 19}},
	{17, {10, 16}},
	{18, {6, 19}},
	{19, {16, 18, 20}},
	{20, {1, 19}}};

/**
 * Mapping to store value of mills possible at each board position
 * @key: position on board
 * @value: mills that can be made with this position
 */
const unordered_map<int, vector<vector<int>>> mills = {
	{0, {{0, 6, 18}}},
	{1, {{1, 11, 20}}},
	{2, {{2, 7, 15}}},
	{3, {{3, 10, 17}}},
	{4, {{4, 8, 12}}},
	{5, {{5, 9, 14}}},
	{6, {{6, 7, 8}, {0, 6, 18}}},
	{7, {{6, 7, 8}, {2, 7, 15}}},
	{8, {{6, 7, 8}, {4, 8, 12}}},
	{9, {{9, 10, 11}, {5, 9, 14}}},
	{10, {{9, 10, 11}, {3, 10, 17}}},
	{11, {{9, 10, 11}, {1, 11, 20}}},
	{12, {{12, 13, 14}, {4, 8, 12}}},
	{13, {{12, 13, 14}, {13, 16, 19}}},
	{14, {{12, 13, 14}, {5, 9, 14}}},
	{15, {{15, 16, 17}, {2, 7, 15}}},
	{16, {{15, 16, 17}, {13, 16, 19}}},
	{17, {{15, 16, 17}, {3, 10, 17}}},
	{18, {{18, 19, 20}, {0, 6, 18}}},
	{19, {{18, 19, 20}, {13, 16, 19}}},
	{20, {{18, 19, 20}, {1, 11, 20}}},
};

/**
 * Mapping to store value of half outer mills possible at each board position
 * @key: position on board
 * @value: half outer mills that can be made with this position
 */
const unordered_map<int, vector<vector<int>>> halfOuterMills = {
	{0, {{0, 18}}},
	{1, {{1, 20}}},
	{2, {{2, 15}}},
	{3, {{3, 17}}},
	{4, {{4, 12}}},
	{5, {{5, 14}}},
	{6, {{6, 8}}},
	{7, {}},
	{8, {{6, 8}}},
	{9, {{9, 11}}},
	{10, {}},
	{11, {{9, 11}}},
	{12, {{12, 14}, {4, 12}}},
	{13, {{13, 19}}},
	{14, {{12, 14}, {5, 14}}},
	{15, {{15, 17}, {2, 15}}},
	{16, {}},
	{17, {{15, 17}, {3, 17}}},
	{18, {{18, 20}, {0, 18}}},
	{19, {{13, 19}}},
	{20, {{18, 20}, {1, 20}}},
};

#endif