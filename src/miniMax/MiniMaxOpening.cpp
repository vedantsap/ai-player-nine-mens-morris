#include "../headers/constants.h"
#include "../headers/board.h"
#include "../headers/prototypes.h"
#include "../headers/fileIO.h"
#include "../headers/staticEstimators.h"
#include "../headers/generator.h"
#include "../headers/minimax.h"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "There should be only 4 parameters! Example : .\\MiniMaxOepening.exe board1.txt board2.txt 2" << endl;
		return -1;
	}
	string currentPosition = readFile(argv[1]);
	cout << "Board as string: " << currentPosition << endl;
	printBoard(currentPosition);
	string newPosition = MiniMaxOpening(currentPosition, atoi(argv[3]));
	printDelta(currentPosition, newPosition);
	printBoard(newPosition);
	writeFile(argv[2], newPosition);
}