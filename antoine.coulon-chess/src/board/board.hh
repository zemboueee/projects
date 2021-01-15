#pragma once

#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "bitwise.hh"
#include "ostream"
#include "pos.hh"
#include "types.hh"

class Move;
class History;

struct army
{
    u64 kings;
    u64 queens;
    u64 rooks;
    u64 bishops;
    u64 knights;
    u64 pawns;
};

enum COLOR
{
    SANS_MAILLOT = 0,
    WHITE = 1,
    BLACK = 2
};

enum GAME_STATUS
{
    PLAYING = 1,
    WHITE_WIN = 1 << 1,
    BLACK_WIN = 1 << 2,
    DRAW = 1 << 3
};

enum PIECE
{
    NONE = 0,

    WHITE_PAWN,
    WHITE_BISHOP,
    WHITE_KNIGHT,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,

    BLACK_PAWN,
    BLACK_BISHOP,
    BLACK_KNIGHT,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING
};

class Board
{
public:
    // board_constructors.cc
    Board();
    Board(std::string str);
    Board(Board& board);

    void init(std::string str);

    // board.cc
    std::vector<Move> getBoardMoves(enum COLOR color);
    std::vector<Move> getMoves(struct pos p);

    u64& getBitboard(struct pos p);

    enum PIECE getElementAtCoord(struct pos p) const;
    enum COLOR getTeam(u8 pos_x, u8 pos_y);

    bool isBlack(struct pos p) const;
    bool isWhite(struct pos p) const;

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    // board_getters.cc
    bool getCastlingLeft(enum COLOR color) const;
    bool getCastlingRight(enum COLOR color) const;
    bool getWhiteTurn() const;
    struct army getWhite() const;
    struct army getBlack() const;
    std::optional<struct pos> getEnpassable() const;

    // board_ia.cc
    size_t getNbPawns(enum COLOR color);
    size_t getNbRooks(enum COLOR color);
    size_t getNbBishops(enum COLOR color);
    size_t getNbKnights(enum COLOR color);
    size_t getNbQueens(enum COLOR color);
    size_t getNbKings(enum COLOR color);

    enum GAME_STATUS getStatus();

    // board_moves.cc
    void applyMove(Move move);

    // ATTRIBUTES
    struct army white;
    struct army black;

private:
    // board_moves.cc
    void handle_castling(Move move);
    void handle_enpassant(Move move);
    void handle_promotion(Move move);
    void updateCastlingAny();

    // ATTRIBUTES
    bool whiteCastlingLeft;
    bool whiteCastlingRight;
    bool blackCastlingLeft;
    bool blackCastlingRight;
    bool castlingAny;
    bool whiteTurn;
    std::optional<struct pos> enpassable;
};

std::ostream& operator<<(std::ostream& os, const Board& b);
