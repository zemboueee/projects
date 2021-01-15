#include <iostream>
#include <string>

#include "bitwise.hh"
#include "boost/program_options.hpp"
#include "game.hh"
#include "gametree.hh"
#include "heuristics.hh"
#include "log.hh"
#include "move.hh"
#include "options.hh"
#include "uci.hh"

#define DEPTH 4

int main(int argc, char* argv[])
{
    parse_options(argc, argv);

    ai::init("myTinyCoreWar");

    while (true)
    {
        std::string str_board = ai::get_board();
        struct UCI uci = parse_UCI(str_board);

        for (Move move : uci.moves)
            uci.board.applyMove(move);

        enum COLOR color = (enum COLOR)((uci.board.getWhiteTurn()) + 1);

        GameTree gt(uci.board, color);

        log("HEURISTIC", "value", main_heuristic(uci.board, color));

        if (color == WHITE)
            log("COLOR", "White");
        else
            log("COLOR", "Black");

        Move move = gt.getBestMove(DEPTH);

        std::string str_move = move.dump(uci.board);

        ai::play_move(str_move);
    }

    return 0;
}
