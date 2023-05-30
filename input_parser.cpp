#include "input_parser.h"

void InputParser::getDataFromUser() {
	std::cin >> game_data.board_size >> game_data.number_of_pieces_that_trigger_collection_of_pieces >> game_data.number_of_white_pieces >> game_data.number_of_black_pieces;
	std::cin >> game_data.reserve_of_white_pieces >> game_data.reserve_of_black_pieces >> game_data.starting_player;

	amount_of_rows = game_data.board_size * 2;
}

void InputParser::getBoardFromUser() {
	for (int i = 0; i < amount_of_rows; i++) {
		std::vector<char> current_line;
		std::string input;
		std::getline(std::cin, input);
		for (int j = 0; j < input.length(); j++) {
			if (input[j] != ' ')
				current_line.push_back(input[j]);
		}
		if(input != "")
			inputed_board.push_back(current_line);
	}
}

bool InputParser::validateBoard() {
	int amount_of_white_pieces_on_board = 0;
	int amount_of_black_pieces_on_board = 0;

	for (int i = 0; i < inputed_board.size(); i++) {
		if ((inputed_board[i].size() != game_data.board_size + i && i <= game_data.board_size - 1) || \
			(inputed_board[i].size() != game_data.board_size + (inputed_board.size() - i - 1) && i > game_data.board_size - 1)) {
			std::cout << "WRONG_BOARD_ROW_LENGTH" << std::endl;
			return false;
		}
		for (int j = 0; j < inputed_board[i].size(); j++) {
			if (inputed_board[i][j] == 'W') amount_of_white_pieces_on_board++;
			else if (inputed_board[i][j] == 'B') amount_of_black_pieces_on_board++;
		}
	}

	if (amount_of_white_pieces_on_board + game_data.reserve_of_white_pieces > game_data.number_of_white_pieces) {
		std::cout << "WRONG_WHITE_PAWNS_NUMBER" << std::endl;
		return false; 
	}
	else if (amount_of_black_pieces_on_board + game_data.reserve_of_black_pieces > game_data.number_of_black_pieces) {
		std::cout << "WRONG_BLACK_PAWNS_NUMBER" << std::endl;
		return false;
	}

	std::cout << "BOARD_STATE_OK" << '\n' << std::endl;
	return true;
}

// Getters

GameData InputParser::getGameData() {
	return this->game_data;
}

std::vector<std::vector<char>> InputParser::getInputedBoard() {
	return this->inputed_board;
}
