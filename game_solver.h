#pragma once
#include <string>
#include <vector>
#include "game.h"
class GameSolver {
private:
	static bool is_board_unique(const std::vector<std::vector<char>>& target, const std::vector<std::vector<std::vector<char>>>& container);
public:
	static int GEN_ALL_POS_MOV_NUM(Game* game);

	static int GEN_ALL_POS_MOV_EXT_NUM(Game* game);

	static std::vector<std::vector<std::vector<char>>> GEN_ALL_POS_MOV(Game* game, bool isFindingWinning=false);

};