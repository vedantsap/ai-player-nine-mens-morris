#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

std::string readFile(std::string fileName){
	std::ifstream boardPositionFile(fileName);
	if (!boardPositionFile)
	{
		std::cout << "invalid file" << std::endl;
	}
	std::string boardPosition;
	boardPositionFile >> boardPosition;
	boardPositionFile.close();
	return boardPosition;
}

void printBoard(std::string board) {
	std::replace(board.begin(), board.end(), 'x', '.');
	std::cout << std::endl;
	std::cout << board[18] << " " << "-" << " " << "-" << " " << board[19] << " " << "-" << " " << "-" << " " << board[20] << std::endl;
	std::cout << "|" << " " << board[15] << " " << "-" << " " << board[16] << " " << "-" << " " << board[17] << " " << "|" << std::endl;
	std::cout << "|" << " " << "|" << " " << board[12] << " " << board[13] << " " << board[14] << " " << "|" << " " << "|" << std::endl;
	std::cout << board[6] << " " << board[7] << " " << board[8] << "   " << board[9] << " " << board[10] << " " << board[11] << std::endl;
	std::cout << "|" << " " << "|" << " " << board[4] << " " << "-" << " " << board[5] << " " << "|" << " " << "|" << std::endl;
	std::cout << "|" << " " << board[2] << " " << "-" << " " << "-" << " " << "-" << " " << board[3] << " " << "|" << std::endl;
	std::cout << board[0] << " " << "-" << " " << "-" << " " << "-" << " " << "-" << " " << "-" << " " << board[1] << std::endl;
    return;
}

int main(int argc, char *argv[]){
	if (argc != 2)
	{
		std::cout << "there should be only 1 parameter" << std::endl;
		return -1;
	}
	std::string currentPosition = readFile(argv[1]);
	printBoard(currentPosition);
	std::cout << currentPosition << std::endl;
}