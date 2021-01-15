#include "board.hh"

#define DEFAULT_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

Board::Board()
{
    init(DEFAULT_FEN);
}

Board::Board(std::string str)
{
    init(str);
}

Board::Board(Board& board)
{
    whiteCastlingLeft = board.getCastlingLeft(WHITE);
    whiteCastlingRight = board.getCastlingLeft(WHITE);
    blackCastlingLeft = board.getCastlingRight(BLACK);
    blackCastlingRight = board.getCastlingRight(BLACK);
    enpassable = board.getEnpassable();
    whiteTurn = board.getWhiteTurn();
    white = board.getWhite();
    black = board.getBlack();
}

void Board::init(std::string str)
{
    black = {};
    black.kings = 0;
    black.queens = 0;
    black.rooks = 0;
    black.bishops = 0;
    black.knights = 0;
    black.pawns = 0;
    white = {};
    white.kings = 0;
    white.queens = 0;
    white.rooks = 0;
    white.bishops = 0;
    white.knights = 0;
    white.pawns = 0;
    int bit = 63;
    size_t i = 0;
    while (str[i] != ' ')
    {
        int lerf_bit = ((((bit / 8) + 1) * 8) - 1) - (bit % 8);
        switch (str[i])
        {
        case 'p':
            black.pawns |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'r':
            black.rooks |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'n':
            black.knights |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'b':
            black.bishops |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'q':
            black.queens |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'k':
            black.kings |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'P':
            white.pawns |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'R':
            white.rooks |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'N':
            white.knights |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'B':
            white.bishops |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'Q':
            white.queens |= setBits(1, lerf_bit);
            bit--;
            break;
        case 'K':
            white.kings |= setBits(1, lerf_bit);
            bit--;
            break;
        default:
            break;
        }
        if (str[i] > '0' && str[i] < '9')
        {
            bit -= (int)(str[i] - '0');
        }
        i++;
    }
    whiteTurn = (str[++i] == 'w');
    i++;
    whiteCastlingLeft = false; // Q
    whiteCastlingRight = false; // K
    blackCastlingLeft = false; // q
    blackCastlingRight = false; // k
    i++;
    while (str[i] != ' ')
    {
        switch (str[i])
        {
        case 'K':
            whiteCastlingRight = true;
        case 'Q':
            whiteCastlingLeft = true;
        case 'k':
            blackCastlingRight = true;
        case 'q':
            blackCastlingLeft = true;
        default:
            break;
        }
        i++;
    }
    updateCastlingAny();
    i++;
    std::string str_pos = "  ";
    if (str[i] == '-')
        enpassable = std::nullopt;
    else
    {
        str_pos[0] = str[i];
        str_pos[1] = str[i + 1];
        enpassable = std::optional<struct pos>(newPos(str_pos));
    }
}
