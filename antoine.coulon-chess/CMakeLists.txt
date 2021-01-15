cmake_minimum_required(VERSION 3.14)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
project(chess)
set(CMAKE_CXX_STANDARD 17)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
    ${CMAKE_SOURCE_DIR}/src/IA
    ${CMAKE_SOURCE_DIR}/src/interface
    ${CMAKE_SOURCE_DIR}/src/misc
)

add_executable(chessengine
		src/main.cc
        src/board/board.cc
        src/board/board_getters.cc
        src/board/board_constructors.cc
        src/board/board_ia.cc
        src/board/board_moves.cc
        src/bitwise.cc
        src/game.cc
        src/move.cc
        src/options.cc
        src/pos.cc
        src/moves/pawn.cc
        src/moves/bishop.cc
        src/moves/knight.cc
        src/moves/rook.cc
        src/moves/queen.cc
        src/moves/king.cc
        src/interface/position.hxx
        src/interface/uci.cc
        src/pgn/pgn-exception.cc
        src/pgn/pgn-move.cc
        src/pgn/pgn-parser.cc
		src/pgn/pgn.cc
        src/IA/gametree.cc
        src/IA/heuristics.cc
        src/misc/tools.cc
        src/misc/log.cc
)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(chessengine ${Boost_LIBRARIES})
