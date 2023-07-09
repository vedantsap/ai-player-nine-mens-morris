#include "../headers/constants.h"
#include "../headers/board.h"
#include "../headers/prototypes.h"
#include "../headers/fileIO.h"
#include "../headers/staticEstimators.h"
#include "../headers/generator.h"
#include "../headers/minimax.h"

using namespace std;

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