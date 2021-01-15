#include "log.hh"

#include <fstream>

void log(std::string tag, std::string str)
{
    std::ofstream file;
    file.open("chessengine.log", std::ios_base::app);
    file << "[" << tag << "] " << str << std::endl;
    file.close();
}

void log(std::string tag, std::string str, int i)
{
    std::ofstream file;
    file.open("chessengine.log", std::ios_base::app);
    file << "[" << tag << "] " << str << ": " << i << std::endl;
    file.close();
}

void log(std::string tag, std::string str, float f)
{
    std::ofstream file;
    file.open("chessengine.log", std::ios_base::app);
    file << "[" << tag << "] " << str << ": " << f << std::endl;
    file.close();
}

void log(std::string tag, Board board)
{
    std::ofstream file;
    file.open("chessengine.log", std::ios_base::app);
    file << "[" << tag << "]\n " << board << std::endl;
    file.close();
}
