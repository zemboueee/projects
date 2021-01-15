#pragma once

#include <string>

#include "board.hh"

void log(std::string tag, std::string str);
void log(std::string tag, std::string str, int i);
void log(std::string tag, std::string str, float f);
void log(std::string tag, Board board);
