#include <iostream>
#include <string>
#include <fstream>

std::string readFile(std::string fileName)
{
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

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "there should be only 1 parameter" << std::endl;
		return -1;
	}
	std::string currentPosition = readFile(argv[1]);
	std::cout << currentPosition << std::endl;
}