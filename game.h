#pragma once

#include "printing_functions.h"
#include "structs.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
class Game {
private:
	GameData game_data;
	std::vector<std::vector<char>> board;
	std::unordered_map<std::string, std::pair<int, int>> board_indexes_map;
public:
	Game() {};

	Game(std::vector<std::vector<char>> _board, GameData _game_data);
	
	void fillBoardIndexesMap();

	~Game() {};
};