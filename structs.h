#pragma once
#include <iostream>
#include <vector>
#include <string>
struct GameData {
	int board_size;
	int number_of_pieces_that_trigger_collection_of_pieces;
	int number_of_white_pieces;
	int number_of_black_pieces;
	int reserve_of_white_pieces;
	int reserve_of_black_pieces;
	char starting_player;
	char current_player;
};

struct Move {
	std::vector<char> line;
	std::vector<std::pair<int, int>> indexes;
	
	std::string start;
	std::string destination;
	
	std::pair<int, int> start_pos;
	std::pair<int, int> destination_pos;

	int index;
	char starter_letter;

	Move(std::string& _start, std::string& _destination, std::pair<int, int>& _start_pos, std::pair<int, int>& _destination_pos) {
		start_pos = _start_pos;
		destination_pos = _destination_pos;
		start = _start;
		destination = _destination;

		index = start[1] - '0' - 1;
		starter_letter = start[0];
	}
};