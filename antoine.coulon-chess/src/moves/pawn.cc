#include <iostream>

#include "moves.hh"
std::vector<Move> getBlackPawnMoves(Board& board, struct pos p,
                                    std::optional<struct pos> enpassable)
{
    std::vector<Move> moves;

    if (p.y == 7) // PROMOTION
        return moves;

    if (board.getTeam(p.x, p.y + 1) == SANS_MAILLOT && p.y < 7)
    {
        if (board.getTeam(p.x, p.y + 2) == SANS_MAILLOT && p.y == 1)
            moves.push_back(Move(p, p.x, p.y + 2));
        moves.push_back(Move(p, p.x, p.y + 1));
    }

    if ((board.getTeam(p.x + 1, p.y + 1) == WHITE
         || (enpassable.has_value() && (enpassable.value()).x == p.x + 1
             && (enpassable.value()).y == p.y
             && board.getTeam((enpassable.value()).x, (enpassable.value()).y)
                 == WHITE))
        && (p.y < 7 && p.x < 7))
        moves.push_back(Move(p, p.x + 1, p.y + 1));

    if ((board.getTeam(p.x - 1, p.y + 1) == WHITE
         || (enpassable.has_value() && (enpassable.value()).x == p.x - 1
             && (enpassable.value()).y == p.y
             && board.getTeam((enpassable.value()).x, (enpassable.value()).y)
                 == WHITE))
        && (p.y < 7 && p.x > 0))
        moves.push_back(Move(p, p.x - 1, p.y + 1));

    return moves;
}

std::vector<Move> getWhitePawnMoves(Board& board, struct pos p,
                                    std::optional<struct pos> enpassable)
{
    std::vector<Move> moves;

    if (p.y == 0)
        return moves;

    if (board.getTeam(p.x, p.y - 1) == SANS_MAILLOT && p.y > 0)
    {
        if (board.getTeam(p.x, p.y - 2) == SANS_MAILLOT && p.y == 6)
            moves.push_back(Move(p, p.x, p.y - 2));

        moves.push_back(Move(p, p.x, p.y - 1));
    }

    if ((board.getTeam(p.x + 1, p.y - 1) == BLACK
         || (enpassable.has_value() && (enpassable.value()).x == p.x + 1
             && (enpassable.value()).y == p.y
             && board.getTeam((enpassable.value()).x, (enpassable.value()).y)
                 == BLACK))
        && (p.y > 0 && p.x < 7))
        moves.push_back(Move(p, p.x + 1, p.y - 1));

    if ((board.getTeam(p.x - 1, p.y - 1) == BLACK
         || (enpassable.has_value() && (enpassable.value()).x == p.x - 1
             && (enpassable.value()).y == p.y
             && board.getTeam((enpassable.value()).x, (enpassable.value()).y)
                 == BLACK))
        && (p.y > 0 && p.x > 0))
        moves.push_back(Move(p, p.x - 1, p.y - 1));
    return moves;
}
