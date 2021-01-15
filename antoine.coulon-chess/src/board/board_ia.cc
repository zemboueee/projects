#include "bitwise.hh"
#include "board.hh"

size_t Board::getNbPawns(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.pawns);
    return getNbSetBit(black.pawns);
}

size_t Board::getNbRooks(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.rooks);
    return getNbSetBit(black.rooks);
}

size_t Board::getNbBishops(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.bishops);
    return getNbSetBit(black.bishops);
}

size_t Board::getNbKnights(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.knights);
    return getNbSetBit(black.knights);
}

size_t Board::getNbQueens(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.queens);
    return getNbSetBit(black.queens);
}

size_t Board::getNbKings(enum COLOR color)
{
    if (color & WHITE)
        return getNbSetBit(white.kings);
    return getNbSetBit(black.kings);
}

enum GAME_STATUS Board::getStatus()
{
    if (getNbKings(WHITE) == 0)
        return BLACK_WIN;
    if (getNbKings(BLACK) == 0)
        return WHITE_WIN;
    return PLAYING;
}
