#include "board.hh"

struct army Board::getWhite() const
{
    return white;
}

struct army Board::getBlack() const
{
    return black;
}

bool Board::getWhiteTurn() const
{
    return whiteTurn;
}

std::optional<struct pos> Board::getEnpassable() const
{
    return enpassable;
}

bool Board::getCastlingLeft(enum COLOR color) const
{
    if (color & WHITE)
        return whiteCastlingLeft;
    if (color & BLACK)
        return blackCastlingLeft;
    return false;
}

bool Board::getCastlingRight(enum COLOR color) const
{
    if (color & WHITE)
        return whiteCastlingRight;
    if (color & BLACK)
        return blackCastlingRight;
    return false;
}
