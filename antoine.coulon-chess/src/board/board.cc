#include "board.hh"

#include "moves/moves.hh"

#define SYMBOL_WHITE_KING "♔"
#define SYMBOL_WHITE_QUEEN "♕"
#define SYMBOL_WHITE_ROOK "♖"
#define SYMBOL_WHITE_BISHOP "♗"
#define SYMBOL_WHITE_KNIGHT "♘"
#define SYMBOL_WHITE_PAWN "♙"

#define SYMBOL_BLACK_KING "♚"
#define SYMBOL_BLACK_QUEEN "♛"
#define SYMBOL_BLACK_ROOK "♜"
#define SYMBOL_BLACK_BISHOP "♝"
#define SYMBOL_BLACK_KNIGHT "♞"
#define SYMBOL_BLACK_PAWN "♟"

enum COLOR Board::getTeam(u8 pos_x, u8 pos_y)
{
    struct pos p = newPos(pos_x, pos_y);
    if (isBlack(p))
        return BLACK;
    if (isWhite(p))
        return WHITE;
    return SANS_MAILLOT;
}

bool Board::isBlack(struct pos p) const
{
    return getPiece(black.kings | black.queens | black.rooks | black.bishops
                        | black.knights | black.pawns,
                    p);
}

bool Board::isWhite(struct pos p) const
{
    return getPiece(white.kings | white.queens | white.rooks | white.bishops
                        | white.knights | white.pawns,
                    p);
}

enum PIECE Board::getElementAtCoord(struct pos p) const
{
    if (isBlack(p))
    {
        if (getPiece(black.pawns, p))
            return BLACK_PAWN;
        if (getPiece(black.rooks, p))
            return BLACK_ROOK;
        if (getPiece(black.bishops, p))
            return BLACK_BISHOP;
        if (getPiece(black.knights, p))
            return BLACK_KNIGHT;
        if (getPiece(black.queens, p))
            return BLACK_QUEEN;
        if (getPiece(black.kings, p))
            return BLACK_KING;
    }

    if (isWhite(p))
    {
        if (getPiece(white.pawns, p))
            return WHITE_PAWN;
        if (getPiece(white.rooks, p))
            return WHITE_ROOK;
        if (getPiece(white.bishops, p))
            return WHITE_BISHOP;
        if (getPiece(white.knights, p))
            return WHITE_KNIGHT;
        if (getPiece(white.queens, p))
            return WHITE_QUEEN;
        if (getPiece(white.kings, p))
            return WHITE_KING;
    }

    return NONE;
}

u64& Board::getBitboard(pos p)
{
    switch (getElementAtCoord(p))
    {
    case WHITE_PAWN:
        return white.pawns;
        break;
    case WHITE_BISHOP:
        return white.bishops;
        break;
    case WHITE_KNIGHT:
        return white.knights;
        break;
    case WHITE_ROOK:
        return white.rooks;
        break;
    case WHITE_QUEEN:
        return white.queens;
        break;
    case WHITE_KING:
        return white.kings;
        break;
    case BLACK_PAWN:
        return black.pawns;
        break;
    case BLACK_BISHOP:
        return black.bishops;
        break;
    case BLACK_KNIGHT:
        return black.knights;
        break;
    case BLACK_ROOK:
        return black.rooks;
        break;
    case BLACK_QUEEN:
        return black.queens;
        break;
    case BLACK_KING:
    default:
        return black.kings;
        break;
    }
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for (u8 y = 0; y < 8; y++)
    {
        os << (int)8 - y;
        for (u8 x = 0; x < 8; x++)
        {
            os << " ";
            struct pos p = {.x = x, .y = y};
            switch (b.getElementAtCoord(p))
            {
            case WHITE_PAWN:
                os << SYMBOL_WHITE_PAWN;
                break;
            case WHITE_BISHOP:
                os << SYMBOL_WHITE_BISHOP;
                break;
            case WHITE_KNIGHT:
                os << SYMBOL_WHITE_KNIGHT;
                break;
            case WHITE_ROOK:
                os << SYMBOL_WHITE_ROOK;
                break;
            case WHITE_QUEEN:
                os << SYMBOL_WHITE_QUEEN;
                break;
            case WHITE_KING:
                os << SYMBOL_WHITE_KING;
                break;
            case BLACK_PAWN:
                os << SYMBOL_BLACK_PAWN;
                break;
            case BLACK_BISHOP:
                os << SYMBOL_BLACK_BISHOP;
                break;
            case BLACK_KNIGHT:
                os << SYMBOL_BLACK_KNIGHT;
                break;
            case BLACK_ROOK:
                os << SYMBOL_BLACK_ROOK;
                break;
            case BLACK_QUEEN:
                os << SYMBOL_BLACK_QUEEN;
                break;
            case BLACK_KING:
                os << SYMBOL_BLACK_KING;
                break;
            case NONE:
                os << ".";
                break;
            }
        }
        os << "\n";
    }
    os << "  A B C D E F G H\n";

    return os;
}

std::vector<Move> Board::getMoves(struct pos p)
{
    enum PIECE piece = getElementAtCoord(p);
    enum COLOR color = getTeam(p.x, p.y);
    std::vector<Move> moves;

    switch (piece)
    {
    case WHITE_PAWN:
        moves = getWhitePawnMoves(*this, p, getEnpassable());
        break;
    case BLACK_PAWN:
        moves = getBlackPawnMoves(*this, p, getEnpassable());
        break;

    case WHITE_BISHOP:
    case BLACK_BISHOP:
        moves = getBishopMoves(*this, color, p);
        break;

    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
        moves = getKnightMoves(*this, color, p);
        break;

    case WHITE_ROOK:
    case BLACK_ROOK:
        moves = getRookMoves(*this, color, p);
        break;

    case WHITE_QUEEN:
    case BLACK_QUEEN:
        moves = getQueenMoves(*this, color, p);
        break;

    case WHITE_KING:
    case BLACK_KING:
        moves = getKingMoves(*this, color, p, getCastlingLeft(color),
                             getCastlingRight(color));
        break;

    case NONE:
        moves = std::vector<Move>();
        break;
    }

    return moves;
}

std::vector<Move> Board::getBoardMoves(enum COLOR color)
{
    std::vector<Move> moves;

    bool (Board::*func)(struct pos) const =
        (color == WHITE) ? &Board::isWhite : &Board::isBlack;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            pos p;
            p.x = j;
            p.y = i;
            if ((this->*func)(p)) // CHECK COLOR
            {
                std::vector<Move> moves_at = getMoves(p);
                moves.insert(moves.end(), moves_at.begin(), moves_at.end());
            }
        }
    }

    return moves;
}
