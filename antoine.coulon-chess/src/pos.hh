#pragma once

#include <ostream>

#include "types.hh"

struct pos
{
    u8 x;
    u8 y;
};

bool oob(struct pos p);
std::ostream& operator<<(std::ostream& os, const struct pos& p);
struct pos newPos(u8 x, u8 y);
struct pos newPos(std::string pos);
