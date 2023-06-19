#include <iostream>
#include <string>
#include <fstream>

class FileIO
{
public:
    std::string readFile(std::string fileName)
    {
        std::ifstream boardPositionFile(fileName);
        if (!boardPositionFile) {
            std::cout << "invalid file" << std::endl;
        }
        std::string boardPosition;
        boardPositionFile >> boardPosition;
        boardPositionFile.close();
        return boardPosition;
    }
}