#pragma once

#include <array>
#include <optional>

namespace board
{
    /* PieceType is an enum representing every possible
     * piece type present on the board. The char associated
     * with each value is the ascii char representing the
     * piece on the board */
    enum class PieceType
    {
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN,
        KING, // Last position allows better optimization (order-move)
    };

    using opt_piecetype_t = std::optional<PieceType>;

    /* Can be useful to iterate over PieceTypes */
    constexpr std::array<PieceType, 6> piecetype_array{
        PieceType::QUEEN,  PieceType::ROOK, PieceType::BISHOP,
        PieceType::KNIGHT, PieceType::PAWN, PieceType::KING};

} // namespace board
