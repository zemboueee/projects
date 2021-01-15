#pragma once
#include <ostream>
#include <vector>

#include "board.hh"
#include "pos.hh"

class Move
{
public:
    Move();
    Move(std::string str);
    Move(struct pos p, u8 dst_x, u8 dst_y);
    friend std::ostream& operator<<(std::ostream& os, const Move& m);
    bool operator==(Move move);
    bool isNull();
    struct pos get_src() const;
    struct pos get_dst() const;
    std::string dump(Board& board);

private:
    struct pos src;
    struct pos dst;
};

std::ostream& operator<<(std::ostream& os, const Move& m);
void printMoves(const std::vector<Move> moves);
void printMovesToSelect(const std::vector<Move> moves);
void removes_oobs(std::vector<Move>& moves, Board& board);
