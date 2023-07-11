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
    	cout << endl;
    	cout << "**************************************************Round: " << ++round << endl;
    	cout << "WHITE played:" << endl;
    	string newPosition = MiniMaxOpening(startPosition, 4); // more than 5 takes too long
    	printDelta(startPosition, newPosition);
    	printBoard(newPosition);

    	cout << endl;
    	cout << "**************************************************Round: " << ++round << endl;
    	cout << "BLACK played:" << endl;
    	startPosition = MiniMaxOpeningBlack(newPosition, 2);
    	printDelta(newPosition, startPosition);
    	printBoard(startPosition);
    }
    cout << "8 pieces used by each player, now entering second phase of game" << endl;

    while (!isWinner(startPosition))
    {
        cout << endl;
        cout << "**************************************************Round: " << ++round << endl;
        cout << "WHITE played:" << endl;
        string newPosition = MiniMaxGame(startPosition, 4); // more than 5 takes too long
        printDelta(startPosition, newPosition);
        printBoard(newPosition);

        cout << endl;
        cout << "**************************************************Round: " << ++round << endl;
        cout << "BLACK played:" << endl;
        startPosition = MiniMaxGameBlack(newPosition, 2);
        printDelta(newPosition, startPosition);
        printBoard(startPosition);

        if (round >= 60)
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

    playAiVsAi(startPosition);
}