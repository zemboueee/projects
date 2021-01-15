#include "pos.hh"

bool oob(struct pos p)
{
    return (p.x > 7 || p.x < 0 || p.y > 7 || p.y < 0);
}

std::ostream& operator<<(std::ostream& os, const struct pos& p)
{
    int x = p.x;
    int y = 8 - p.y;
    if (y < 0)
        y = ((y + 255) % 255) + 1;
    if (y > 127)
        y = -(256 - y);

    if (x > 127)
    {
        x = 255 - x;
        return os << "-" << (char)('a' + x) << y;
    }
    return os << (char)('a' + x) << y;
}

struct pos newPos(u8 x, u8 y)
{
    struct pos p;
    p.x = x;
    p.y = y;

    return p;
}

struct pos newPos(std::string pos)
{
    struct pos p;
    p.x = (int)(pos[0] - 'a');
    p.y = 8 - (int)(pos[1] - '0');

    return p;
}
