#include "pgn.hh"

std::vector<Move> pgnMovesToMoves(std::vector<board::PgnMove> pgnMoves)
{
    std::vector<Move> moves;
    for (auto pgnMove : pgnMoves)
        moves.push_back(pgnMovetoMove(pgnMove));
    return moves;
}

Move pgnMovetoMove(board::PgnMove pgnMove)
{
    pos src = positionToPos(pgnMove.getStart());
    pos dst = positionToPos(pgnMove.getEnd());
    Move move(src, dst.x, dst.y);

    return move;
}

struct pos positionToPos(board::Position position)
{
    struct pos pos;
    switch (position.rank_get())
    {
    case board::Rank::ONE:
        pos.y = 7;
        break;
    case board::Rank::TWO:
        pos.y = 6;
        break;
    case board::Rank::THREE:
        pos.y = 5;
        break;
    case board::Rank::FOUR:
        pos.y = 4;
        break;
    case board::Rank::FIVE:
        pos.y = 3;
        break;
    case board::Rank::SIX:
        pos.y = 2;
        break;
    case board::Rank::SEVEN:
        pos.y = 1;
        break;
    case board::Rank::EIGHT:
        pos.y = 0;
        break;
    }

    switch (position.file_get())
    {
    case board::File::A:
        pos.x = 0;
        break;
    case board::File::B:
        pos.x = 1;
        break;
    case board::File::C:
        pos.x = 2;
        break;
    case board::File::D:
        pos.x = 3;
        break;
    case board::File::E:
        pos.x = 4;
        break;
    case board::File::F:
        pos.x = 5;
        break;
    case board::File::G:
        pos.x = 6;
        break;
    case board::File::H:
        pos.x = 7;
        break;
    }

    return pos;
}
