#include "../src/headers/constants.h"
#include "../src/headers/board.h"
#include "../src/headers/prototypes.h"
#include "../src/headers/fileIO.h"
#include "../src/headers/staticEstimators.h"
#include "../src/headers/generator.h"
#include "../src/headers/minimax.h"

int main(int argc, char *argv[])
{
    string startPosition = EMPTY_BOARD;
    if (argc < 2)
    {
        cout << "Starting with empty board, WHITE to play first" << endl;
    }
    else
    {
        startPosition = argv[1];
        cout << "Starting with board " << startPosition << ", WHITE play first" << endl;
    }
    printBoard(startPosition);
    int estimate = staticEstimationMidgameEndgame(startPosition);
    cout << endl
         << "Calculated static estimate for above board: " << estimate << endl;
}