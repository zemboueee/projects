#pragma once

#include "board.hh"
#include "move.hh"
#include "types.hh"

class GameTree
{
public:
    GameTree(Board& board, enum COLOR color);
    Move getBestMove(u8 depth);

    float min(Board& board, u8 depth);
    float max(Board& board, u8 depth);

    float eval(Board& board, enum COLOR eval_color);

private:
    Board root;
    enum COLOR color;
    enum COLOR color_opponent;
};
