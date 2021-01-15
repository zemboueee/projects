#include <list>

#include "board.hh"
#include "move.hh"

class Game
{
public:
    Game();

    std::list<Move> getValidMoves(Board board);

    void loadPGN(std::string path);
    int calculPERFT();

    Board getBoard();

private:
    Board board;
};
