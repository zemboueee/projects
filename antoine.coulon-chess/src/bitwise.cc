#include "bitwise.hh"

#include <cstdarg>
#include <iostream>

#include "pos.hh"

size_t getNbSetBit(u64& bitboard)
{
    size_t sum = 0;
    for (u64 i = 1; i != 0; i <<= 1)
        sum += (bool)(bitboard & i);
    return sum;
}

void setBit(u64& bitboard, int offset)
{
    bitboard |= ((u64)1 << offset);
}

void unsetBit(u64& bitboard, int offset)
{
    bitboard &= ~((u64)1 << offset);
}

void removePiece(u64& bitboard, struct pos p)
{
    unsetBit(bitboard, posToIndex(p));
}

void addPiece(u64& bitboard, struct pos p)
{
    setBit(bitboard, posToIndex(p));
}

u64 setBits(int n_args...)
{
    // Set bits for LERBEF mapping mode

    va_list args;
    va_start(args, n_args);
    u64 res = 0;

    for (int i = 0; i < n_args; i++)
    {
        int index = va_arg(args, int);
        setBit(res, index);
    }

    va_end(args);

    return res;
}

bool getBit(u64 bitboard, unsigned offset)
{
    return bitboard & ((u64)1 << offset);
}

bool getPiece(u64 bitboard, struct pos p)
{
    return getBit(bitboard, posToIndex(p));
}

unsigned posToIndex(struct pos p)
{
    return ((8 - p.y) * 8) + p.x - 8;
}

void printBitboard(std::string name, u64 bitboard)
{
    std::cout << "===== " << name << " =====\n";
    for (u8 y = 0; y < 8; y++)
    {
        std::cout << (int)8 - y;
        for (u8 x = 0; x < 8; x++)
        {
            std::cout << " ";
            struct pos p = {.x = x, .y = y};
            switch (bitboard & ((u64)1 << posToIndex(p)))
            {
            case 0:
                std::cout << ".";
                break;
            default:
                std::cout << "X";
                break;
            }
        }
        std::cout << "\n";
    }
    std::cout << "  A B C D E F G H\n";
}
