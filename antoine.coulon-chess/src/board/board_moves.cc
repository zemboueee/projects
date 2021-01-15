#include "board.hh"
#include "move.hh"
#include "moves/moves.hh"

void Board::applyMove(Move move)
{
    if (castlingAny)
        handle_castling(move);
    handle_enpassant(move);
    handle_promotion(move);

    u64& bitboard = getBitboard(move.get_src());

    // Remove the soldier
    removePiece(bitboard, move.get_src());

    // Remove the soldier Kill on his bitboard (if killed)
    if (getElementAtCoord(move.get_dst()) != NONE)
        removePiece(getBitboard(move.get_dst()), move.get_dst());

    addPiece(bitboard, move.get_dst());
}

void Board::handle_promotion(Move move)
{
    if (move.get_dst().y == 0
        && getElementAtCoord(move.get_src()) == WHITE_PAWN)
    {
        removePiece(white.pawns, move.get_src());
        addPiece(white.queens, move.get_src());
    }

    if (move.get_dst().y == 7
        && getElementAtCoord(move.get_src()) == BLACK_PAWN)
    {
        removePiece(black.pawns, move.get_src());
        addPiece(black.queens, move.get_src());
    }
}

void Board::handle_castling(Move move)
{
    if (move.get_src().x == 4)
    {
        // WHITE
        if (move.get_src().y == 7)
        {
            // updates castling states (WHITE KING)
            whiteCastlingLeft = false;
            whiteCastlingRight = false;
            updateCastlingAny();
            if (move.get_dst().y == 7)
            {
                // RIGHT WHITE
                if (move.get_dst().x == 6)
                {
                    if (getElementAtCoord(newPos(4, 7)) == WHITE_KING)
                    {
                        applyMove(Move(newPos(7, 7), 5, 7));
                    }
                }
                // LEFT WHITE
                else if (move.get_dst().x == 2)
                {
                    if (getElementAtCoord(newPos(4, 7)) == WHITE_KING)
                    {
                        applyMove(Move(newPos(0, 7), 3, 7));
                    }
                }
            }
        }
        // BLACK
        else if (move.get_src().y == 0)
        {
            // updates castling states (BLACK KING)
            blackCastlingLeft = false;
            blackCastlingRight = false;
            updateCastlingAny();
            if (move.get_dst().y == 0)
            {
                // RIGHT BLACK
                if (move.get_dst().x == 6)
                {
                    if (getElementAtCoord(newPos(4, 0)) == BLACK_KING)
                    {
                        applyMove(Move(newPos(7, 0), 5, 0));
                    }
                }
                // LEFT BLACK
                else if (move.get_dst().x == 2)
                {
                    if (getElementAtCoord(newPos(4, 0)) == BLACK_KING)
                    {
                        applyMove(Move(newPos(0, 0), 3, 0));
                    }
                }
            }
        }
    }
    // updates castling states (LEFT ROOKS)
    else if (move.get_src().x == 0)
    {
        if (move.get_src().y == 7)
        {
            whiteCastlingLeft = false;
            updateCastlingAny();
        } else if (move.get_src().y == 0)
        {
            blackCastlingLeft = false;
            updateCastlingAny();
        }
    }
    // updates castling states (RIGHT ROOKS)
    else if (move.get_src().x == 7)
    {
        if (move.get_src().y == 7)
        {
            whiteCastlingRight = false;
            updateCastlingAny();
        } else if (move.get_src().y == 0)
        {
            blackCastlingRight = false;
            updateCastlingAny();
        }
    }
}

void Board::handle_enpassant(Move move)
{
    bool pawn = false;
    if (enpassable.has_value())
    {
        enum PIECE piece = getElementAtCoord(move.get_src());
        if (piece == WHITE_PAWN)
        {
            pawn = true;
            if (getElementAtCoord(enpassable.value()) == BLACK_PAWN)
            {
                if ((move.get_src().x != move.get_dst().x)
                    && (getTeam(move.get_dst().x, move.get_dst().y)
                        == SANS_MAILLOT))
                {
                    removePiece(getBitboard(enpassable.value()),
                                enpassable.value());
                }
            }
        } else if (piece == BLACK_PAWN)
        {
            pawn = true;
            if (getElementAtCoord(enpassable.value()) == WHITE_PAWN)
            {
                if ((move.get_src().x != move.get_dst().x)
                    && (getTeam(move.get_dst().x, move.get_dst().y)
                        == SANS_MAILLOT))
                {
                    removePiece(getBitboard(enpassable.value()),
                                enpassable.value());
                }
            }
        }
    }
    if (std::abs(move.get_src().y - move.get_dst().y) == 2)
    {
        if (pawn)
        {
            enpassable = std::optional<struct pos>(move.get_dst());
            return;
        }
        enum PIECE piece = getElementAtCoord(move.get_src());
        if (piece == WHITE_PAWN || piece == BLACK_PAWN)
        {
            enpassable = std::optional<struct pos>(move.get_dst());
            return;
        }
    }
    enpassable = std::nullopt;
}

void Board::updateCastlingAny()
{
    castlingAny = whiteCastlingRight || whiteCastlingLeft || blackCastlingRight
        || blackCastlingLeft;
}
