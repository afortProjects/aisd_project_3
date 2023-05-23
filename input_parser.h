#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class InputParser {
private:
	int board_size;
	int number_of_pieces_that_trigger_collection_of_pieces;
	int number_of_white_pieces;
	int number_of_black_pieces;
	int reserve_of_white_pieces;
	int reserve_of_black_pieces;
	char starting_player;
	std::vector<std::vector<char>> inputed_board;

	int amount_of_rows;
public:
	std::vector<std::vector<char>> board;
	std::unordered_map<std::string, std::pair<int, int>> board_indexes_map;
	
	InputParser() {};

	void getDataFromUser();

	void getBoardFromUser();

	void printUserData();

	void printUserBoard();

	void validateBoard();

	void fillBoardIndexesMap();

	~InputParser() {};

};