#pragma Once

#include <vector>

#include "../move.hh"
#include "../pos.hh"
#include "pgn-move.hh"

std::vector<Move> pgnMovesToMoves(std::vector<board::PgnMove> pgnMoves);
Move pgnMovetoMove(board::PgnMove pgnMove);
struct pos positionToPos(board::Position position);
