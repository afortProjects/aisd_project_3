#include "printing_functions.h"

void printData(GameData& game_data) {
	std::cout << "Board size " << game_data.board_size << std::endl;
	std::cout << "Number of pieces that trigger collection of pieces " << game_data.number_of_pieces_that_trigger_collection_of_pieces << std::endl;
	std::cout << "Number of black pieces " << game_data.number_of_black_pieces << std::endl;
	std::cout << "Number of white pieces " << game_data.number_of_white_pieces << std::endl;
	std::cout << "Reserve of white pieces " << game_data.reserve_of_white_pieces << std::endl;
	std::cout << "Reserve of black pieces " << game_data.reserve_of_black_pieces << std::endl;
	std::cout << "Starting player " << game_data.starting_player << std::endl;
}

void printBoard(std::vector<std::vector<char>>& inputed_board, GameData& game_data) {
	for (int i = 0; i < inputed_board.size(); i++) {
		for (int v = 0; v < (game_data.board_size * 2  - 1) - inputed_board[i].size() - 1; v++) std::cout << ' ';
		for (int j = 0; j < inputed_board[i].size(); j++) {
			std::cout << inputed_board[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}