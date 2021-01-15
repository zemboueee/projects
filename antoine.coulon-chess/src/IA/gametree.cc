#include "gametree.hh"

#include <cmath>
#include <cstdlib>

#include "heuristics.hh"
#include "log.hh"
#include "tools.hh"

GameTree::GameTree(Board& board, enum COLOR color)
{
    root = Board(board);
    this->color = color;
    this->color_opponent = getOpponentColor(color);
}

Move GameTree::getBestMove(u8 depth)
{
    // MINMAX

    float max_value = -INFINITY;
    std::vector<Move> board_moves = root.getBoardMoves(color);

    Move best_move = board_moves[rand() % board_moves.size()];

    for (Move move : board_moves)
    {
        Board new_board = Board(root);
        new_board.applyMove(move);
        float value = min(new_board, depth - 1);
        if (value > max_value)
        {
            max_value = value;
            best_move = move;
        }
    }

    return best_move;
    /*
    int i = rand() % board_moves.size();
    Move move = board_moves[i];
    return move;
    */
}

float GameTree::min(Board& board, u8 depth)
{
    float min_value = INFINITY;
    std::vector<Move> board_moves = board.getBoardMoves(color_opponent);
    Move best_move = board_moves[0];

    // fin de recursion ou fin du jeu (echec et mat ou draw)
    if (depth == 0 || board_moves.size() == 0)
        return eval(board, color);

    for (Move move : board_moves)
    {
        Board new_board = Board(board);
        new_board.applyMove(move);

        float value = max(new_board, depth - 1);
        if (value < min_value)
            min_value = value;
    }

    return min_value;
}

float GameTree::max(Board& board, u8 depth)
{
    float max_value = -INFINITY;
    std::vector<Move> board_moves = board.getBoardMoves(color);

    // fin de recursion ou fin du jeu (echec et mat ou draw)
    if (depth == 0 || board_moves.size() == 0)
        return eval(board, color);

    Move best_move = board_moves[0];

    for (Move move : board_moves)
    {
        Board new_board = Board(board);
        new_board.applyMove(move);

        float value = min(new_board, depth - 1);
        if (value > max_value)
            max_value = value;
    }

    return max_value;
}

float GameTree::eval(Board& board, enum COLOR eval_color)
{
    if (board.getStatus() != PLAYING)
    {
        if ((eval_color & WHITE) && (board.getStatus() & WHITE_WIN))
            return INFINITY;
        else if ((eval_color & BLACK) && (board.getStatus() & BLACK_WIN))
            return INFINITY;
        else if ((eval_color & BLACK) && (board.getStatus() & WHITE_WIN))
            return -INFINITY;
        else if ((eval_color & WHITE) && (board.getStatus() & BLACK_WIN))
            return -INFINITY;
        else
            return 0;
    }

    return main_heuristic(board, eval_color);
}
