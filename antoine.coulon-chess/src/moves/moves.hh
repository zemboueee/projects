#pragma once
#include "../move.hh"

std::vector<Move> getWhitePawnMoves(Board& board, struct pos p,
                                    std::optional<struct pos> enpassable);
std::vector<Move> getBlackPawnMoves(Board& board, struct pos p,
                                    std::optional<struct pos> enpassable);

std::vector<Move> getBishopMoves(Board& board, enum COLOR color, struct pos p);

std::vector<Move> getKnightMoves(Board& board, enum COLOR color, struct pos p);

std::vector<Move> getRookMoves(Board& board, enum COLOR color, struct pos p);

std::vector<Move> getQueenMoves(Board& board, enum COLOR color, struct pos p);

std::vector<Move> getKingMoves(Board& board, enum COLOR color, struct pos p,
                               bool castlingLeft, bool castlingRight);
