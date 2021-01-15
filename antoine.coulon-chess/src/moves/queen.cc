#include "moves.hh"

std::vector<Move> getQueenMoves(Board& board, enum COLOR color, struct pos p)
{
    std::vector<Move> moves;

    std::vector<Move> bishopMoves = getBishopMoves(board, color, p);
    std::vector<Move> rookMoves = getRookMoves(board, color, p);

    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());

    return moves;
}
