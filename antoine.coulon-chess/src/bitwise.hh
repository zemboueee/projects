#pragma once
#include <string>

#include "types.hh"

size_t getNbSetBit(u64& bitboard);
void setBit(u64& bitboard, int offset);
void unsetBit(u64& bitboard, int offset);

void removePiece(u64& bitboard, struct pos p);
void addPiece(u64& bitboard, struct pos p);

u64 setBits(int n_args...);

bool getBit(u64 bitboard, unsigned offset);

bool getPiece(u64 bitboard, struct pos p);

unsigned posToIndex(pos p);

void printBitboard(std::string name, u64 bitboard);
