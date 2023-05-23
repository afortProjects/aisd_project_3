#include "input_parser.h"

void InputParser::getDataFromUser() {
	std::cin >> board_size >> number_of_pieces_that_trigger_collection_of_pieces >> number_of_white_pieces >> number_of_black_pieces;
	std::cin >> reserve_of_white_pieces >> reserve_of_black_pieces >> starting_player;
	amount_of_rows = board_size * 2;
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
		inputed_board.push_back(current_line);
	}
}

void InputParser::printUserData() {
	std::cout << "Board size " << board_size << std::endl;
	std::cout << "Number of pieces that trigger collection of pieces " << number_of_pieces_that_trigger_collection_of_pieces << std::endl;
	std::cout << "Number of black pieces " << number_of_black_pieces << std::endl;
	std::cout << "Number of white pieces " << number_of_white_pieces << std::endl;
	std::cout << "Reserve of white pieces " << reserve_of_white_pieces << std::endl;
	std::cout << "Reserve of black pieces " << reserve_of_black_pieces << std::endl;
	std::cout << "Starting player " << starting_player << std::endl;
}

void InputParser::printUserBoard() {
	for (int i = 0; i < inputed_board.size(); i++) {
		for (int v = 0; v < amount_of_rows - inputed_board[i].size() -  1; v++) std::cout << ' ';
		for (int j = 0; j < inputed_board[i].size(); j++) {
			std::cout << inputed_board[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void InputParser::fillBoardIndexesMap() {

}
