#ifndef FILEIO_H
#define FILEIO_H

#include "constants.h"

string readFile(string fileName)
{
	ifstream boardPositionFile(fileName);
	if (!boardPositionFile)
	{
		throw runtime_error("invalid file");
	}
	string boardPosition;
	boardPositionFile >> boardPosition;
	if (boardPosition.size() != BOARD_SIZE)
	{
		throw runtime_error("invalid board position within file");
	}
	boardPositionFile.close();
	return boardPosition;
}

void writeFile(string fileName, string board)
{
	ofstream boardPositionFile(fileName);
	if (boardPositionFile.is_open())
	{
		boardPositionFile << board;
		boardPositionFile.close();
	}
	else
	{
		throw runtime_error("Could not write output board to file!");
	}
}

#endif