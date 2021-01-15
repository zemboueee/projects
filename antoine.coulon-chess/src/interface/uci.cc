#include "uci.hh"

#include <fnmatch.h>
#include <iostream>

#include "log.hh"

namespace ai
{
    namespace
    {
        std::string get_input(const std::string& expected = "*")
        {
            // Get a command following the expected globbing
            // Ignoring all unrecognized commands
            std::string buffer;
            do
            {
                std::getline(std::cin, buffer);
                if ("quit" == buffer || "stopuci" == buffer)
                    exit(0);
            } while (fnmatch(expected.c_str(), buffer.c_str(), 0));
            return buffer;
        }
    } // namespace

    void init(const std::string& name)
    {
        get_input("uci");
        std::cout << "id name " << name << '\n';
        std::cout << "id author " << name << '\n';
        std::cout << "uciok" << std::endl;
        get_input("isready");
        std::cout << "readyok" << std::endl;
    }

    void play_move(const std::string& move)
    {
        // Send the computed move
        std::cout << "bestmove " << move << std::endl;
    }

    std::string get_board()
    {
        auto board = get_input("position *"); // Get the board
        get_input("go *"); // Wait for a go from GUI
        return board;
    }
} // namespace ai

#if 0
struct UCI
{
    Board board;
    std::vector<Move> moves;
};
#endif

struct UCI parse_UCI(std::string str)
{
    log("UCI", str);
    struct UCI uci;
    if (str.length() == 0)
    {
        uci.board = Board();
        uci.moves = std::vector<Move>();
        return uci;
    }
    size_t i = 0;
    while (i < str.length() && str[i] != ' ')
        i++;

    ++i;
    if (i < str.length() && str[i] == 's')
    {
        uci.board = Board();
    } else
    {
        if (i >= str.length())
        {
            uci.board = Board();
            uci.moves = std::vector<Move>();
            return uci;
        }

        while (i < str.length() && str[i] != ' ')
            i++;
        uci.board = Board(str.substr(++i));
    }

    i = str.find("moves");
    if (i == std::string::npos)
    {
        uci.moves = std::vector<Move>();
        return uci;
    }

    while (i < str.length() && str[i] != ' ')
        i++;

    while (i < str.length())
    {
        i++;
        uci.moves.push_back(Move(str.substr(i, i + 4)));
        while (str[i] != ' ')
            i++;
    }
    return uci;
}
