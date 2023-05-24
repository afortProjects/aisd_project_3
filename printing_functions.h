#pragma once

#include <iostream>
#include <vector>

#include "structs.h"

void printData(GameData& game_data);

void printBoard(std::vector<std::vector<char>> inputed_board, GameData& game_data);
