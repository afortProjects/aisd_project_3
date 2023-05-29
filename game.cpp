#include "game.h"

Game::Game(std::vector<std::vector<char>> _board, GameData _game_data) : board(_board), game_data(_game_data) {
	// Surround board with X -> starter points for pawns
	
	// First and last rows
	std::vector<char> temp_vector;
	for (int i = 0; i < game_data.board_size+1; i++) {
		temp_vector.push_back('X');
	}
	board.insert(board.begin(), temp_vector);
	board.push_back(temp_vector);

	// Edges

	for (int i = 1; i < board.size()-1; i++) {
		board[i].insert(board[i].begin(), 'X');
		board[i].push_back('X');
	}
	
	game_data.current_player = game_data.starting_player;

	fillBoardIndexesMap();
}

void Game::printBoard() {
	std::cout << game_data.board_size << " " << game_data.number_of_pieces_that_trigger_collection_of_pieces << " " << game_data.number_of_white_pieces << " " << game_data.number_of_black_pieces << std::endl;
	std::cout << game_data.reserve_of_white_pieces << " " << game_data.reserve_of_black_pieces << " " << game_data.current_player << std::endl;
	for (int i = 1; i < board.size() - 1; i++) {
		for (int v = 1; v < (game_data.board_size * 2 + 1) - board[i].size() +1; v++) std::cout << ' ';
		for (int j = 1; j < board[i].size() - 1; j++) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Game::printGameState() {
	std::cout << game_state << std::endl;
}

void Game::fillBoardIndexesMap() {
	int start = game_data.board_size;
	int max_board_row_length = start * 2 + 1;

	int x = start;
	int y = 0;

	int letter_counter = 0;
	int position_counter = 1;

	while (start != max_board_row_length) {
		while (x >= 0) {
			std::string board_index = alphabet[letter_counter] + std::to_string(position_counter);
			std::cout << board_index << " " << x << " " << y << std::endl;
			this->board_indexes_map[board_index] = std::pair<int, int>{ x, y};
			x--;
			position_counter++;
		}
		y++;
		x = start + 1;
		start++;
		position_counter = 1;
		letter_counter++;
	}

	int limiter = 1;
	start--;
	x--;

	while (start != game_data.board_size) {
		while (x >= limiter) {
			std::string board_index = alphabet[letter_counter] + std::to_string(position_counter);
			std::cout << board_index << " " << x << " " << y << std::endl;
			this->board_indexes_map[board_index] = std::pair<int, int>{ x, y };
			x--;
			position_counter++;
		}
		x = max_board_row_length - 1;
		y++;

		position_counter = 1;
		letter_counter++;
		start--;
		limiter++;
	}
}

bool Game::validateMove(std::pair<int, int>& start_pos, std::pair<int, int>& destination_pos, std::string& start, std::string& destination) {
	//Check if start_pos and destination_pos arent null - werent found in hashmap
	if (board[destination_pos.first][destination_pos.second] == 'X') {
		game_status = "BAD_MOVE_" + destination + "_IS_WRONG_DESTINATION_FIELD";
		return false;
	}
	if (board[start_pos.first][start_pos.second] == 'X') {
		/*if (start_pos.first == 0 && start_pos.second == 0) {
			if (destination_pos.first == start_pos.first + 1 && destination_pos.second == start_pos.second + 1) {
				return true;
			}
		}
		else if (start_pos.first == 0 && start_pos.second == game_data.board_size) {
			if (destination_pos.first == start_pos.first + 1 && destination_pos.second == start_pos.first) {
				return true;
			}
		}
		else if (start_pos.first == game_data.board_size && start_pos.second == 0) {
			if (destination_pos.second == start_pos.second + 1 && start_pos.first == destination_pos.first) {
				return true;
			}
		}
		else if (start_pos.first == game_data.board_size && start_pos.second == game_data.board_size * 2 + 1) {
			if (destination_pos.second == start_pos.second - 1 && start_pos.first == destination_pos.first) {
				return true;
			}
		}
		else if (start_pos.first == game_data.board_size + 1 && start_pos.second == 0) {
			if ((destination_pos.first == start_pos.first - 1 && destination_pos.second == start_pos.second + 1) || (destination_pos.second == start_pos.second + 1 && destination_pos.first == start_pos.first)) {
				return true;
			}
		}
		else if (start_pos.first == game_data.board_size + 1 && start_pos.second == game_data.board_size * 2) {
			if (destination_pos.first == start_pos.first - 1 && destination_pos.second == start_pos.second) {
				return true;
			}
		}
		else {
			if ((destination_pos.first == start_pos.first + 1 && destination_pos.second == start_pos.second) || (destination_pos.second == start_pos.second + 1 && destination_pos.first == start_pos.first)) {
				return true;
			}
			if ((destination_pos.first == start_pos.first - 1 && destination_pos.second == start_pos.second + 1) || (destination_pos.first == start_pos.first && destination_pos.second == start_pos.second+1)) {
				return true;
			}
			if ((destination_pos.first == start_pos.first - 1 && destination_pos.second == start_pos.second - 1) || (destination_pos.first == start_pos.first - 1 && destination_pos.second == start_pos.second + 1)) {
				return true;
			}
		}*/

		//TODO: review
		if (start_pos.first == destination_pos.first && start_pos.second + 1 == destination_pos.second) {
			return true;
		}
		if (start_pos.first - 1 == destination_pos.first && start_pos.second + 1 == destination_pos.second) {
			return true;
		}
		if (start_pos.first - 1 == destination_pos.first && start_pos.second == start_pos.second) {
			return true;
		}
		if (start_pos.first == destination_pos.first && start_pos.second - 1 == destination_pos.second) {
			return true;
		}
		if ((start_pos.first + 1 == destination_pos.first && start_pos.second == destination_pos.second) || (start_pos.first == destination_pos.first && start_pos.second + 1 == destination_pos.second)) {
			return true;
		}
	}
	else {
		game_status = "BAD_MOVE_" + start + "_IS_WRONG_STARTING_FIELD";
		return false;
	}
	game_status = "UNKNOWN_MOVE_DIRECTION";
	return false;
}

bool shiftVectorByRightIfFoundPlacce(std::vector<char>& line, char& current_player) {
	int index = 0;
	auto iterator = std::find(line.begin(), line.end(), '_');
	if (std::count(line.begin(), line.end(), '_') > 0) {
		if (iterator != line.end()) {
			index = static_cast<int> (std::distance(line.begin(), iterator));
		}
		for (int i = index; i > 0; i--) {
			line[i] = line[i - 1];
		}
		line[0] = current_player;
		return true;
	}
	return false;
}


bool Game::checkIfMoveDoesntPushAnyPieceToTheEdge(std::pair<int, int>& start_pos, std::pair<int, int>& destination_pos, std::string& start, std::string& destination) {
	// TODO: check, handle index 0 and last
		// Line 
		if (destination_pos.first == start_pos.first) {
			if (std::count(board[start_pos.first].begin(), board[start_pos.first].end(), '_') > 0) {
				int index = 0;
				auto iterator = std::find(board[start_pos.first].begin(), board[start_pos.first].end(), '_');

				if (iterator != board[start_pos.first].end()) {
					index = static_cast<int> (std::distance(board[start_pos.first].begin(), iterator));
				}
				if (start_pos.second == 0) {
					for (int i = index; i > 1; i--) {
						board[start_pos.first][i] = board[start_pos.first][i - 1];
					}
					board[start_pos.first][0] = game_data.current_player;
				}
				else {
					for (int i = board[start_pos.first].size() - 2; i > index + 1; i--) {
						board[start_pos.first][i] = board[start_pos.first][i - 1];
					}
					board[start_pos.first][board[start_pos.first].size() - 1] = game_data.current_player;
				}
				return false;
			}
		}
		else {
			std::vector<char> line;
			char starter_letter = start[0];
			int counter = start[1] - '0';
			int counter_copy = counter;
			if (destination_pos.second > game_data.board_size) {
				while (counter_copy > 2) {
					std::string new_index = starter_letter + std::to_string(counter_copy);
					std::pair<int, int> new_index_pos = board_indexes_map[new_index];
					line.push_back(board[new_index_pos.first][new_index_pos.second]);
					counter_copy--;
				}
				if (shiftVectorByRightIfFoundPlacce(line, game_data.current_player)) {
					counter_copy = counter;
					while (counter_copy > 2) {
						std::string new_index = starter_letter + std::to_string(counter_copy);
						std::pair<int, int> new_index_pos = board_indexes_map[new_index];
						board[new_index_pos.first][new_index_pos.second] = line[line.size() - counter_copy];
						counter_copy--;
					}
					return false;
				}
			}
			else {
				int off = ( start[1] - '0' ) + 1;
				for (size_t i = starter_letter - 'a' - 1; i < 2 * game_data.board_size + off ; i++) {
					std::string new_index = alphabet[i] + std::to_string(counter_copy);
					std::pair<int, int> new_index_pos = board_indexes_map[new_index];
					line.push_back(board[new_index_pos.first][new_index_pos.second]);
				}
				if (shiftVectorByRightIfFoundPlacce(line, game_data.current_player)) {
					counter = 0;
					for (size_t i = alphabet.find(starter_letter); i < 2 * game_data.board_size - static_cast<int>(start[1]) - 1; i++) {
						std::string new_index = alphabet[i] + std::to_string(counter_copy);
						std::pair<int, int> new_index_pos = board_indexes_map[new_index];
						board[new_index_pos.first][new_index_pos.second] = line[counter];
					}
					return false;
				}
			}
		}

	
	game_status = "BAD_MOVE_ROW_IS_FULL";
	return true;
}


void Game::doMove(std::string start, std::string destination) {
	checkIfPlayerLost();
	
	//Check if indexes exists in hash map
	if (board_indexes_map.count(start) == 0) {
		game_status = "BAD_MOVE_" + start + "_IS_WRONG_INDEX";
	} 
	else if (board_indexes_map.count(destination) == 0) {
		game_status = "BAD_MOVE_" + destination + "_IS_WRONG_INDEX";
	}
	else {
		std::pair<int, int> start_pos = board_indexes_map[start];
		std::pair<int, int> destination_pos = board_indexes_map[destination];

		if (validateMove(start_pos, destination_pos, start, destination)) {
			if (!checkIfMoveDoesntPushAnyPieceToTheEdge(start_pos, destination_pos, start, destination)) {
				//After placing the piece, remove it from reserve
				if (game_data.current_player == 'B') {
					game_data.reserve_of_black_pieces--;
				}
				else {
					game_data.reserve_of_white_pieces--;
				}

				//Next player's turn
				game_data.current_player = board[destination_pos.first][destination_pos.second] == 'B' ? 'W' : 'B';

				game_status = "MOVE_COMMITED";
			}
		}
	}
	//else {
	//	game_state = "bad_move";
	//}
	std::cout << game_status << std::endl;
}

bool Game::checkIfPlayerLost() {
	int reserve = game_data.current_player == 'B' ? game_data.reserve_of_black_pieces : game_data.reserve_of_white_pieces;
	if (reserve == 0) return true;
	return false;
}