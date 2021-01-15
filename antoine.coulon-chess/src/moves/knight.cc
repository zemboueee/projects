#include "moves.hh"

std::vector<Move> getKnightMoves(Board& board, enum COLOR color, struct pos p)
{
    std::vector<Move> moves;

    int xs[8] = {1, 1, -1, -1, -2, -2, 2, 2};
    int ys[8] = {-2, 2, -2, 2, 1, -1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        if (p.x + xs[i] < 8 && p.y + ys[i] < 8 && p.x + xs[i] >= 0
            && p.y + ys[i] >= 0)
        {
            u8 x = p.x + xs[i];
            u8 y = p.y + ys[i];
            if (board.getTeam(x, y) != color)
                moves.push_back(Move(p, x, y));
        }
    }

    return moves;
}
