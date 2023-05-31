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
	
	std::pair<bool, int> validateBoard();

	bool validateMove(Move& move);

	bool shiftVectorByRightIfFoundPlace(std::vector<char>& line);

	bool handleLineMovement(Move& move);

	bool handleTopLeftMovement(Move& move);

	bool handleTopRightMovement(Move& move);

	bool handleBottomLeftMovement(Move& move);

	bool handleBottomRightMovement(Move& move);

	bool checkIfMoveDoesntPushAnyPieceToTheEdge(Move& move);

	void doMove(std::string start, std::string destination);

	~Game() {};
};