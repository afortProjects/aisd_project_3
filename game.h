#pragma once

#include "structs.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
class Game {
private:
	std::string alphabet = "abcdefghijklmnoprstwuxyz";
	std::string game_status;
	std::string game_state;
	GameData game_data;
	std::vector<std::vector<char>> board;
	std::unordered_map<std::string, std::pair<int, int>> board_indexes_map;
public:
	Game() {};

	Game(std::vector<std::vector<char>> _board, GameData _game_data);
	
	void printBoard();

	void printGameState();

	void fillBoardIndexesMap();
	
	bool checkIfPlayerLost();

	bool validateMove(std::pair<int, int>& start_pos, std::pair<int, int>& destination_pos, std::string& start, std::string& destination);

	bool checkIfMoveDoesntPushAnyPieceToTheEdge(std::pair<int, int>& start_pos, std::pair<int, int>& destination_pos, std::string& start, std::string& destination);

	void doMove(std::string start, std::string destination);

	~Game() {};
};