#include "tools.hh"

enum COLOR getOpponentColor(enum COLOR color)
{
    return (enum COLOR)((2 - color) + 1);
}
