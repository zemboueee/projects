#include "move.hh"

#include <iostream>
#include <sstream>

#include "bitwise.hh"

Move::Move(struct pos p, u8 dst_x, u8 dst_y)
{
    src = p;
    dst.x = dst_x;
    dst.y = dst_y;
}

Move::Move(std::string str)
{
    std::string str_src = str.substr(0, 2);
    std::string str_dst = str.substr(2, 4);
    src = newPos(str_src);
    dst = newPos(str_dst);
}

Move::Move()
{
    src.x = 0;
    src.y = 0;
    dst.x = 0;
    dst.y = 0;
}

std::ostream& operator<<(std::ostream& os, const Move& m)
{
    return os << m.src << " -> " << m.dst;
}

void printMoves(const std::vector<Move> moves)
{
    u64 bitboard = 0;

    for (size_t i = 0; i < moves.size(); i++)
        addPiece(bitboard, moves[i].get_dst());

    printBitboard("Moves", bitboard);
}

void printMovesToSelect(const std::vector<Move> moves)
{
    std::cout << "===== "
              << "Moves"
              << " =====\n";
    for (u8 y = 0; y < 8; y++)
    {
        std::cout << (int)8 - y;
        for (u8 x = 0; x < 8; x++)
        {
            bool b = true;
            std::cout << " ";
            for (size_t i = 0; i < moves.size(); i++)
            {
                if (moves[i].get_dst().x == x && moves[i].get_dst().y == y)
                {
                    std::cout << i;
                    b = false;
                }
            }
            if (b)
                std::cout << ".";
        }
        std::cout << "\n";
    }
    std::cout << "  A B C D E F G H\n";
}

bool Move::operator==(Move move)
{
    return src.x == move.get_src().x && src.y == move.get_src().y
        && dst.x == move.get_dst().x && dst.y == move.get_dst().y;
}

bool Move::isNull()
{
    return src.x == 0 && src.y == 0 && dst.x == 0 && dst.y == 0;
}

struct pos Move::get_dst() const
{
    return dst;
}

struct pos Move::get_src() const
{
    return src;
}

std::string Move::dump(Board& board)
{
    std::stringstream ss;
    ss << src;
    ss << dst;
    if (dst.y == 0 && board.getElementAtCoord(src) == WHITE_PAWN
        || dst.y == 7 && board.getElementAtCoord(src) == BLACK_PAWN)
        ss << 'q';

    return ss.str();
}

void removes_oobs(std::vector<Move>& moves, Board& board)
{
    for (auto it = moves.begin(); it < moves.end(); it++)
        if (oob(it->get_dst()))
            moves.erase(it);
}
