#pragma once

#include "structs.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
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

	void splitLineAndIndexes(std::string& line, std::vector<std::string>& indexes, std::vector<std::string>& splitted_line, std::vector<std::vector<std::string>>& splitted_indexes);

	void checkForLinesOfPiecesInBoard(int& counter, std::string& line, std::vector<std::string> indexes, int board_index, bool is_move);
	
	std::pair<bool, int> handleSelectedMove(bool& was_selected_found, std::string& row, int counter, std::string& start, std::string& destination, char color, std::vector<char>& line, std::vector < std::string >& indexes);

	std::pair<bool, int> validateBoard(bool is_move, bool is_selected_which_pieces_to_take = false, char color = 'N', std::string start = "", std::string destination = "");

	void calculatePoints(int count, char color);

	bool validateMove(Move& move);

	bool shiftVectorByRightIfFoundPlace(std::vector<char>& line);

	bool handleLineMovement(Move& move);

	bool handleTopLeftMovement(Move& move);

	bool handleTopRightMovement(Move& move);

	bool handleBottomLeftMovement(Move& move);

	bool handleBottomRightMovement(Move& move);

	bool checkIfMoveDoesntPushAnyPieceToTheEdge(Move& move);

	void doMove(std::string start, std::string destination, bool is_selected_which_pieces_to_take = false, char color = 'N', std::string start_selected = "", std::string dest_selected = "");

	~Game() {};
};