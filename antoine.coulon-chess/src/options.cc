#include "options.hh"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "board.hh"
#include "boost/program_options.hpp"
#include "game.hh"
#include "move.hh"
#include "pgn/pgn-parser.hh"
#include "pgn/pgn.hh"

void on_pgn(std::string path)
{
    std::cout << "path to the PGN game file: " << path << std::endl;
    std::vector<Move> moves = pgnMovesToMoves(pgn_parser::parse_pgn(path));

    Game game;
    Board board = game.getBoard();

    for (int i = 0; i < moves.size(); i++)
    {
        std::vector<Move> moves_available = board.getBoardMoves(WHITE);
        std::vector<Move> moves_available_black = board.getBoardMoves(BLACK);
        moves_available.insert(moves_available.end(),
                               moves_available_black.begin(),
                               moves_available_black.end());

        if (std::find(moves_available.begin(), moves_available.end(), moves[i])
            != moves_available.end())
        {
            board.applyMove(moves[i]);
            std::cout << i << ": " << moves[i] << " -> OK NICE\n";
        } else
        {
            std::cout << board;
            board.applyMove(moves[i]);
            std::cout << i << ": " << moves[i] << " -> ARCHI MAL\n";
            std::cout << board;
            exit(0);
            return;
        }
    }
    exit(0);
}

void on_listerners(std::vector<std::string> paths)
{}

void on_perft(std::string path)
{
    std::ifstream is(path);
    std::stringstream ss;
    ss << is.rdbuf();
    std::string str = ss.str();
    Board board = Board(str);
    if (board.getWhiteTurn())
        std::cout << board.getBoardMoves(WHITE).size() << std::endl;
    else
        std::cout << board.getBoardMoves(BLACK).size() << std::endl;
    std::cout << board << std::endl;
    exit(0);
}

void dumpGame(Board board)
{
    std::cout << board << std::endl;
}

void on_debug()
{
    std::cout << "Welcome to Chess\n";
    Game game;

    Board board = game.getBoard();

    dumpGame(board);

    while (true)
    {
        std::cout << "Position (A7, G2, H8...)? ";
        // int position;
        std::string position;
        std::cin >> position;
        if (!position.compare("T"))
            break;
        pos p;
        p.x = (int)(position[0] - 'A');
        p.y = 8 - (int)(position[1] - '0');
        std::vector<Move> white_moves = board.getBoardMoves(WHITE);
        std::vector<Move> black_moves = board.getBoardMoves(BLACK);
        printMoves(white_moves);
        printMoves(black_moves);

        std::vector<Move> moves = board.getMoves(p);
        if (moves.size() != 0)
        {
            for (size_t i = 0; i < moves.size(); i++)
                std::cout << "N°" << i << ": " << moves[i] << std::endl;
            printMovesToSelect(moves);

            std::cout << "move N°? ";
            int move_number;
            std::cin >> move_number;
            board.applyMove(moves[move_number]);
        }

        dumpGame(board);
    }
}

void parse_options(int argc, char* argv[])
{
    try
    {
        boost::program_options::options_description desc("Allowed options");

        // clang-format off
        // Options Description
        desc.add_options()

            ("help,h", "show usage")

            ("pgn",
                boost::program_options::value<std::string>()
                ->notifier(on_pgn),
            "path to the PGN game file")

            ("listerners,l",
                boost::program_options::value<std::vector<std::string>>()
                ->multitoken()
                ->notifier(on_listerners),
            "list of paths to listener plugins")

            ("perft",
                boost::program_options::value<std::string>()
                ->notifier(on_perft),
            "path to a perft file")

            ("debug,d", "play a game of chess");
        // Fin de zone ODd
        // clang-format on

        boost::program_options::variables_map vm;
        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
        // --help
        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            std::exit(0);
        }
        // --debug
        if (vm.count("debug"))
        {
            on_debug();
            std::exit(0);
        }
    } catch (std::exception& e)
    {
        std::cerr << "usage: --help" << std::endl;
        exit(1);
    }
}
