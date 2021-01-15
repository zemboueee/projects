#include "heuristics.hh"

#include "misc/tools.hh"

#define PAWN_VALUE 100
#define KNIGHT_VALUE 320
#define BISHOP_VALUE 330
#define ROOK_VALUE 500
#define QUEEN_VALUE 900
#define KING_VALUE 20000 * 100

float main_heuristic(Board board, enum COLOR color)
{
    return heuristic_pieces_sum(board, color);
}

float heuristic_pieces_sum(Board board, enum COLOR color)
{
    size_t nb_pawns = board.getNbPawns(color);
    size_t nb_rooks = board.getNbRooks(color);
    size_t nb_bishops = board.getNbBishops(color);
    size_t nb_knights = board.getNbKnights(color);
    size_t nb_queens = board.getNbQueens(color);
    size_t nb_kings = board.getNbKings(color);

    enum COLOR color_opponent = getOpponentColor(color);

    size_t nb_opponent_pawns = board.getNbPawns(color_opponent);
    size_t nb_opponent_rooks = board.getNbRooks(color_opponent);
    size_t nb_opponent_bishops = board.getNbBishops(color_opponent);
    size_t nb_opponent_knights = board.getNbKnights(color_opponent);
    size_t nb_opponent_queens = board.getNbQueens(color_opponent);
    size_t nb_opponent_kings = board.getNbKings(color_opponent);

    size_t sum = PAWN_VALUE * nb_pawns + ROOK_VALUE * nb_rooks
        + BISHOP_VALUE * nb_bishops + KNIGHT_VALUE * nb_knights
        + QUEEN_VALUE * nb_queens + KING_VALUE * nb_kings;

    size_t sum_opponent = PAWN_VALUE * nb_opponent_pawns
        + ROOK_VALUE * nb_opponent_rooks + BISHOP_VALUE * nb_opponent_bishops
        + KNIGHT_VALUE * nb_opponent_knights + QUEEN_VALUE * nb_opponent_queens
        + KING_VALUE * nb_opponent_kings;

    return (float)((float)sum - (float)sum_opponent);
}
