#include "game.hh"

#include "board.hh"

Game::Game()
    : board()
{}

std::list<Move> Game::getValidMoves(Board board)
{
    return std::list<Move>();
}

void Game::loadPGN(std::string path)
{}

int Game::calculPERFT()
{
    return 0;
}

Board Game::getBoard()
{
    return board;
}
