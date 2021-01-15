#include "moves.hh"

std::vector<Move> getRookMoves(Board& board, enum COLOR color, struct pos p)
{
    std::vector<Move> moves;

    int xs[4] = {1, -1, 0, 0};
    int ys[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; p.x + (j * xs[i]) < 8 && p.y + (j * ys[i]) < 8
             && p.x + (j * xs[i]) >= 0 && p.y + (j * ys[i]) >= 0;
             j++)
        {
            u8 x = p.x + (j * xs[i]);
            u8 y = p.y + (j * ys[i]);
            enum COLOR team = board.getTeam(x, y);
            if (team != SANS_MAILLOT)
            {
                if (team != color)
                    moves.push_back(Move(p, x, y));

                break;
            }
            moves.push_back(Move(p, x, y));
        }
    }

    return moves;
}
