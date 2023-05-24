#pragma once
#include "structs.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class InputParser {
private:
	GameData game_data;
	std::vector<std::vector<char>> inputed_board;
	int amount_of_rows;

public:
	
	InputParser() {};

	void getDataFromUser();

	void getBoardFromUser();

	bool validateBoard();

	// Getters

	GameData getGameData();

	std::vector<std::vector<char>> getInputedBoard();

	~InputParser() {};

};