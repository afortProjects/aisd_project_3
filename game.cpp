#include "game.h"

Game::Game(std::vector<std::vector<char>> _board, GameData _game_data) : board(_board), game_data(_game_data) {
	// Surround board with X -> starter points for pawns
	// First and last rows
	std::vector<char> temp_vector;
	for (int i = 0; i < game_data.board_size; i++) {
		temp_vector.push_back('X');
	}
	board.insert(board.begin(), temp_vector);
	board.push_back(temp_vector);

	// Edges

	for (int i = 1; i < board.size()-1; i++) {
		board[i].insert(board[i].begin(), 'X');
		board[i].push_back('X');
	}
	
	fillBoardIndexesMap();
}

void Game::fillBoardIndexesMap() {
	//TODO: clean
	//for (int i = 0; i < board.size(); i++) {
	//	for (int v = 0; v < (game_data.board_size * 2 + 1) - board[i].size() +1; v++) std::cout << ' ';
	//	for (int j = 0; j < board[i].size(); j++) {
	//		std::cout << board[i][j] << ' ';
	//	}
	//	std::cout << std::endl;
	//}
	std::string alphabet = "abcdefghijklmnoprstwuxyz";
	int L = game_data.board_size;
	int S = L * 2 + 1;

	int counter = L;
	int position_counter = 1;
	int col = 0;

	int letter_counter = 0;
	// Up

	while (L != S) {
		while (counter >= 0) {
			std::string board_index = alphabet[letter_counter] + std::to_string(position_counter);
			std::cout << board_index << " " << counter << " " << col << std::endl;
			this->board_indexes_map[board_index] = std::pair<int, int>{ counter, col};
			counter--;
			position_counter++;
		}
		col++;
		counter = L + 1;
		L++;
		position_counter = 1;
		letter_counter++;
	}

	// Down
	L--;
	counter = S - 1;
	int counter_col = 1;
	while (L != game_data.board_size) {
		while (counter >= counter_col) {
			std::string board_index = alphabet[letter_counter] + std::to_string(position_counter);
			std::cout << board_index << " " << counter  << " " << col << std::endl;
			this->board_indexes_map[board_index] = std::pair<int, int>{ counter, col };
			counter--;
			position_counter++;
		}
		col++;
		counter = S - 1;
		counter_col++;
		L--;
		position_counter = 1;
		letter_counter++;
	}	
}
