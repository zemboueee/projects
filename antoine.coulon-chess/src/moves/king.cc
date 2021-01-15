#include "moves.hh"

std::vector<Move> getKingMoves(Board& board, enum COLOR color, struct pos p,
                               bool castlingLeft, bool castlingRight)
{
    std::vector<Move> moves;

    int xs[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int ys[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

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

    if (p.x == 4)
    {
        if (p.y == 7)
        {
            if (castlingRight)
            {
                // WHITE KING    4, 7 -> 6, 7
                // WHITE TOWER   7, 7 -> 5, 7
                if ((board.getTeam(5, 7) | board.getTeam(6, 7)) == SANS_MAILLOT)
                    moves.push_back(Move(p, 6, 7));
            }
            if (castlingLeft)
            {
                // WHITE KING    4, 7 -> 2, 7
                // WHITE TOWER   0, 7 -> 3, 7
                if ((board.getTeam(1, 7) | board.getTeam(2, 7)
                     | board.getTeam(3, 7))
                    == SANS_MAILLOT)
                    moves.push_back(Move(p, 2, 7));
            }

        } else if (p.y == 0)
        {
            if (castlingRight)
            {
                // BLACK KING    4, 0 -> 6, 0
                // BLACK TOWER   7, 0 -> 5, 0
                if ((board.getTeam(5, 0) | board.getTeam(6, 0)) == SANS_MAILLOT)
                    moves.push_back(Move(p, 6, 0));
            }
            if (castlingLeft)
            {
                // BLACK KING    4, 0 -> 2, 0
                // BLACK TOWER   0, 0 -> 3, 0
                if ((board.getTeam(1, 0) | board.getTeam(2, 0)
                     | board.getTeam(3, 0))
                    == SANS_MAILLOT)
                    moves.push_back(Move(p, 2, 0));
            }
        }
    }

    return moves;
}
