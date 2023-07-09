#include "../src/headers/constants.h"
#include "../src/headers/board.h"
#include "../src/headers/prototypes.h"
#include "../src/headers/fileIO.h"
#include "../src/headers/staticEstimators.h"
#include "../src/headers/generator.h"
#include "../src/headers/minimax.h"

using namespace std;

void playAiVsAi(string startPosition)
{
    cout << "Starting game AI vs AI. WHITE to play first!" << endl;
    int round = 0;
    for (int i = 0; i < 8; i++)
    {
    	// FOR RANDOM GAME
    	// vector<string> whiteMoves = generateAdd(startPosition);
    	// string newPosition = whiteMoves[rand() % whiteMoves.size()];
    	cout << endl;
    	cout << "**************************************************Round: " << ++round << endl;
    	cout << "WHITE played:" << endl;
    	string newPosition = MiniMaxOpening(startPosition, 4); // more than 5 takes too long
    	printDelta(startPosition, newPosition);
    	printBoard(newPosition);

    	// FOR RANDOM GAME
    	// string invertedBoard = invertBoard(newPosition);
    	// vector<string> blackMovesInverted = generateAdd(invertedBoard);
    	// string startPositionInverted = blackMovesInverted[rand() % blackMovesInverted.size()];
    	cout << endl;
    	cout << "**************************************************Round: " << ++round << endl;
    	cout << "BLACK played:" << endl;
    	startPosition = invertBoard(MiniMaxOpening(invertBoard(newPosition), 2));
    	printDelta(newPosition, startPosition);
    	printBoard(startPosition);
    }
    cout << "8 pieces used by each player, now entering second phase of game" << endl;

    while (!isWinner(startPosition))
    {
        cout << endl;
        cout << "**************************************************Round: " << ++round << endl;
        cout << "WHITE played:" << endl;
        string newPosition = MiniMaxGame(startPosition, 2); // more than 5 takes too long
        printDelta(startPosition, newPosition);
        printBoard(newPosition);

        cout << endl;
        cout << "**************************************************Round: " << ++round << endl;
        cout << "BLACK played:" << endl;
        startPosition = invertBoard(MiniMaxGame(invertBoard(newPosition), 3));
        printDelta(newPosition, startPosition);
        printBoard(startPosition);

        if (round >= 100)
        {
            cout << "~~~~~!! GAME TIED AT ROUND " << round << " !!~~~~~" << endl;
            return;
        }

        if (isWinner(invertBoard(startPosition)))
        {
            cout << "~~~~~!! BLACK WINS !!~~~~~" << endl;
            return;
        }
    }
    cout << "~~~~~!! WHITE WINS !!~~~~~" << endl;
    return;
}

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

    // string midEndGameSample = "xWWBxBWWWBWxxxWxWxxBx";
    playAiVsAi(startPosition);
}