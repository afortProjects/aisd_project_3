#include "game.h"


Game::Game(std::vector<std::vector<char>> _board, GameData _game_data) : board(_board), game_data(_game_data) {
	// Surround board with X -> starter points for pawns

	// First and last rows
	std::vector<char> temp_vector;
	for (int i = 0; i < (game_data.board_size) + 1; i++) {
		temp_vector.push_back('X');
	}
	board.insert(board.begin(), temp_vector);
	board.push_back(temp_vector);

	// Edges

	for (int i = 1; i < board.size() - 1; i++) {
		board[i].insert(board[i].begin(), 'X');
		board[i].push_back('X');
	}

	for (auto& v : board) {
		int difference = game_data.board_size * 2 + 1 - v.size();
		while (difference != 0) {
			v.insert(v.begin(), ' ');
			difference--;
		}
	}

	game_data.current_player = game_data.starting_player;

	fillBoardIndexesMap();
}

void Game::printBoard() {
	std::cout << game_data.board_size << " " << game_data.number_of_pieces_that_trigger_collection_of_pieces << " " << game_data.number_of_white_pieces << " " << game_data.number_of_black_pieces << std::endl;
	std::cout << game_data.reserve_of_white_pieces << " " << game_data.reserve_of_black_pieces << " " << game_data.current_player << std::endl;
	for (auto& row : board) {
		int counter = 0;

		for (auto& element : row) {
			if (element != 'X') {
				std::cout << element;
				if (element != ' ')
					std::cout << ' ';
				else
					counter++;
			}
		}
		for (int i = 0; i < counter; i++) std::cout << ' ';
		std::cout << std::endl;
	}
}

void Game::printGameState() {
	std::cout << game_state << std::endl;
}

void Game::fillBoardIndexesMap() {
	int counter_pos = 0;
	for (int i = 0; i < board.size(); i++) {
		if (i <= game_data.board_size) {
			int counter = 0;
			int letter_counter = 0;
			for (int j = 0; j < board.size(); j++) {
				if (board[i][j] != ' ') {
					std::string board_index;
					if (j > board.size() - 1 - counter_pos) {
						counter = board.size() - 1;
						board_index = alphabet[letter_counter] + std::to_string(counter + 1 - counter_pos);
					} else 
						board_index = alphabet[letter_counter] + std::to_string(counter + 1);

					//std::cout << board_index << " " << i << " " << j << counter_pos << std::endl;

					this->board_indexes_map[board_index] = std::pair<int, int>{ i , j };
					letter_counter++;
				}
				counter++;
			}
			counter_pos++;
		}
		else {
			int letter_counter = i - game_data.board_size;
			int counter = 0;
			for (int j = 0; j < board.size(); j++) {
				if (board[i][j] != ' ') {
					std::string board_index;
					if (j >= counter_pos) {
						board_index = alphabet[letter_counter] + std::to_string(counter);
					}
					else
						board_index = alphabet[letter_counter] + std::to_string(counter + 1);

					//std::cout << board_index << " " << i << " " << j << counter_pos << std::endl;

					this->board_indexes_map[board_index] = std::pair<int, int>{ i , j };
					letter_counter++;
					
					if(j < counter_pos)
						counter++;
				}
			}
			if(counter_pos < game_data.board_size+1)
				counter_pos++;	
		}
	}
}

bool Game::checkIfPlayerLost() {
	int reserve = game_data.current_player == 'B' ? game_data.reserve_of_black_pieces : game_data.reserve_of_white_pieces;
	if (reserve == 0) {
		game_state = game_data.current_player == 'B' ? "black_win" : "white_win";
		return true;
	}
	return false;
}

void Game::calculatePoints(int count, char color) {
	if (color == 'B') {
		game_data.reserve_of_black_pieces += count;
	}
	else {
		game_data.reserve_of_white_pieces += count;
	}
}

void Game::splitLineAndIndexes(std::string& line, std::vector<std::string>& indexes, std::vector<std::string>& splitted_line, std::vector<std::vector<std::string>>& splitted_indexes) {
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == 'X' || line[i] == ' ') {
			line[i] = ' ';
			if (indexes.size() > 0) {
				indexes[i] = " ";
			}
		}
	}
	indexes.erase(std::remove(indexes.begin(), indexes.end(), " "), indexes.end());
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	int temp_counter = 0;

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '_') {
			std::string temp = line.substr(temp_counter, i - temp_counter);
			if (temp != "") splitted_line.push_back(temp);
			if (indexes.size() >= 1) {
				std::vector<std::string> temp_vector;
				for (int j = temp_counter; j < i; j++) {
					temp_vector.push_back(indexes[j]);
				}
				if (temp_counter == i + 1) temp_vector.push_back(indexes[i]);

				if (temp_vector.size() >= 1) {
					splitted_indexes.push_back(temp_vector);

				}
			}
			temp_counter = i + 1;
		}
	}

	if (temp_counter < line.size()) {
		splitted_line.push_back(line.substr(temp_counter, line.size() - temp_counter));
		if (indexes.size() >= 1) {
			std::vector<std::string> temp_vector;
			for (int j = temp_counter; j < line.size(); j++) {
				temp_vector.push_back(indexes[j]);
			}
			splitted_indexes.push_back(temp_vector);
		}
	}
}

void Game::checkForLinesOfPiecesInBoard(int& counter, std::string& line, std::vector<std::string> indexes, int board_index, bool is_move) {
	std::vector<std::string> splitted_line;
	std::vector<std::vector<std::string>> splitted_indexes;
	splitLineAndIndexes(line, indexes, splitted_line, splitted_indexes);

	for (int i = 0; i < splitted_line.size(); i++) {
		std::string token = splitted_line[i];
		int count = 1;
		if (token != "" && token.size() >= 2) {
			for (int h = 0; h < token.size() - 1; h++) {
				if (token[h] == token[h + 1]) {
					count++;
				}
				else {
					if (count >= game_data.number_of_pieces_that_trigger_collection_of_pieces) {
						if (board_index != NULL && is_move) {
							std::string board_line(board[board_index].begin(), board[board_index].end());
							size_t pos = board_line.find(token); 
							std::string cleared_line(token.size(), '_');
							if (pos != std::string::npos) { 
								board_line.replace(pos, token.size(), cleared_line); 
							}
							for (int v = 1; v < board[board_index].size() - 2; v++) {
								board[board_index][v] = board_line[v];
							}
						}
						else if (is_move) {
							for (auto& ind : splitted_indexes[i]) {
								std::pair<int, int> position = board_indexes_map[ind];
								board[position.first][position.second] = '_';
							}
							break;
						}

						counter++;
						calculatePoints(count, token[h]);

					}
					count = 1;
				}
			}
			//If there wasn't _ at the end
			if (count >= game_data.number_of_pieces_that_trigger_collection_of_pieces) {
				if (board_index != NULL && is_move) {
					std::string board_line(board[board_index].begin(), board[board_index].end());
					size_t pos = board_line.find(token);
					std::string cleared_line(token.size(), '_');
					if (pos != std::string::npos) {
						board_line.replace(pos, token.size(), cleared_line);
					}
					for (int v = 1; v < board[board_index].size() - 2; v++) {
						board[board_index][v] = board_line[v];
					}
				}
				if (splitted_indexes.size() >= 1 && is_move) {
					for (auto& ind : splitted_indexes.back()) {
						std::pair<int, int> position = board_indexes_map[ind];
						board[position.first][position.second] = '_';
					}
				}
				if (std::count(token.begin(), token.end(), 'B') > std::count(token.begin(), token.end(), 'W')) {
					calculatePoints(count, 'B');
				}
				else {
					calculatePoints(count, 'W');
				}
				counter++;
			}
		}
	}
}

std::pair<bool, int> Game::validateBoard(bool is_move) {
	//Lines
	int counter = 0;
	for (int i = 0; i < board.size(); i++) {
		//Split string by -
		std::string row (board[i].begin(), board[i].end());
		checkForLinesOfPiecesInBoard(counter, row, std::vector<std::string> (), i, is_move);
	}

	//Diagonally (a1-a2-a3...-a_n)
	int amount_of_letters = 2 * game_data.board_size + 1;
	for (int i = 0; i < amount_of_letters; i++) {
		std::vector<char> line;
		std::vector < std::string > indexes;
		
		int position_counter = 1;
		std::string index = alphabet[i] + std::to_string(position_counter);
		
		while (board_indexes_map.count(index) != 0) {
			std::pair<int, int> pos = board_indexes_map[index];
			line.push_back(board[pos.first][pos.second]);
			indexes.push_back(index);
			position_counter++;
			index = alphabet[i] + std::to_string(position_counter);
		}

		std::string row (line.begin(), line.end());
		checkForLinesOfPiecesInBoard(counter, row, indexes, NULL, is_move);
	}

	//Diagonally a5-b5-c5-d5-e5...i-1
	int starter = game_data.board_size + 1;
	int covered_counter = 0;
	int position_counter = 1;
	int number_of_smaller_position_counter = 0;
	int letter_starter = 0;

	while (covered_counter < game_data.board_size * 2 + 1) {
		int letter_counter = letter_starter;
		int copied_counter = position_counter;
		std::vector<char> line;
		std::vector<std::string> indexes;

		for (int i = letter_starter; i < starter - letter_starter; i++) {
			std::string index;
			if (i >= starter - number_of_smaller_position_counter ) {
				copied_counter--;
				index = alphabet[letter_counter] + std::to_string(copied_counter);
			}
			else {
				index = alphabet[letter_counter] + std::to_string(position_counter);
			}
			std::pair<int, int> pos = board_indexes_map[index];
			line.push_back(board[pos.first][pos.second]);
			indexes.push_back(index);
			letter_counter++;
		}

		std::string row(line.begin(), line.end());
		checkForLinesOfPiecesInBoard(counter, row, indexes, NULL, is_move);

		position_counter++;
		number_of_smaller_position_counter++;
		covered_counter++;
		starter++;

		if (starter >= game_data.board_size * 2 + 1) {
			letter_starter++;
		}
	}

	if (counter == 0)
		return std::pair<bool, int> {true, 0};
	else 
		return std::pair<bool, int> { false, counter };
}

bool Game::validateMove(Move& move) {
	//Check if start_pos and destination_pos arent null - werent found in hashmap
	if (board[move.destination_pos.first][move.destination_pos.second] == 'X') {
		game_status = "BAD_MOVE_" + move.destination + "_IS_WRONG_DESTINATION_FIELD";
		return false;
	}
	//TODO: CHECK
	if (board[move.start_pos.first][move.start_pos.second] == 'X') {
		if (move.start_pos.first == move.destination_pos.first && move.start_pos.second + 1 == move.destination_pos.second) {
			return true;
		}
		if (move.start_pos.first - 1 == move.destination_pos.first && move.start_pos.second - 1 == move.destination_pos.second) {
			return true;
		}
		if (move.start_pos.first - 1 == move.destination_pos.first && move.start_pos.second + 1 == move.destination_pos.second) {
			return true;
		}
		if (move.start_pos.first - 1 == move.destination_pos.first && move.start_pos.second == move.destination_pos.second) {
			return true;
		}
		if (move.start_pos.first + 1 == move.destination_pos.first && move.start_pos.second-1 == move.destination_pos.second) {
			return true;
		}
		if (move.start_pos.first == move.destination_pos.first && move.start_pos.second - 1 == move.destination_pos.second) {
			return true;
		}
		if ((move.start_pos.first + 1 == move.destination_pos.first && move.start_pos.second == move.destination_pos.second) || (move.start_pos.first == move.destination_pos.first && move.start_pos.second + 1 == move.destination_pos.second)) {
			return true;
		}
		if ((move.start_pos.first + 1 == move.destination_pos.first && move.start_pos.second + 1== move.destination_pos.second) || (move.start_pos.first + 1== move.destination_pos.first && move.start_pos.second + 1 == move.destination_pos.second)) {
			return true;
		}
	}
	else {
		game_status = "BAD_MOVE_" + move.start + "_IS_WRONG_STARTING_FIELD";
		return false;
	}
	game_status = "UNKNOWN_MOVE_DIRECTION";
	return false;
}

bool Game::shiftVectorByRightIfFoundPlace(std::vector<char>& line) {
	int index = 0;
	auto iterator = std::find(line.begin(), line.end(), '_');
	if (std::count(line.begin(), line.end(), '_') > 0) {
		if (iterator != line.end()) {
			index = static_cast<int> (std::distance(line.begin(), iterator));
		}
		for (int i = index; i > 0; i--) {
			line[i] = line[i - 1];
		}
		line[0] = game_data.current_player;
		return true;
	}
	return false;
}

bool Game::handleLineMovement(Move& move) {
	if (std::count(board[move.start_pos.first].begin(), board[move.start_pos.first].end(), '_') > 0) {
		int index = 0;
		auto iterator = std::find(board[move.start_pos.first].begin(), board[move.start_pos.first].end(), '_');

		if (iterator != board[move.start_pos.first].end()) {
			index = static_cast<int> (std::distance(board[move.start_pos.first].begin(), iterator));
		}

		if (move.start_pos.second < game_data.board_size) {
			for (int i = index; i > 1; i--) {
				board[move.start_pos.first][i] = board[move.start_pos.first][i - 1];
			}
			board[move.start_pos.first][1] = game_data.current_player;
		}
		else {
			for (int i = index; i < board[move.start_pos.first].size() - 2; i++) {
				board[move.start_pos.first][i] = board[move.start_pos.first][i + 1];
			}
			board[move.start_pos.first][board[move.start_pos.first].size() - 2] = game_data.current_player;
		}
		return true;
	}
	return false;
}

bool Game::handleTopLeftMovement(Move& move) {
	if (move.start_pos.second <= game_data.board_size) {
		int skip = 2 * game_data.board_size - 1 - move.start_pos.first;
		int counter = move.start_pos.second;
		for (int i = 1 + move.start_pos.first; i < skip + 1; i++) {
			if (i > game_data.board_size)
				counter++;
			move.indexes.push_back(std::pair<int, int>(i, counter));
			move.line.push_back(board[i][counter]);
		}

		if (shiftVectorByRightIfFoundPlace(move.line)) {
			for (int i = 0; i < move.line.size(); i++) {
				board[move.indexes[i].first][move.indexes[i].second] = move.line[i];
			}
			return true;
		}

	}
	return false;
}

bool Game::handleTopRightMovement(Move& move) {
	int counter = move.index;
	while (counter >= 2) {
		std::string new_index = move.starter_letter + std::to_string(counter);
		std::pair<int, int> new_index_pos = board_indexes_map[new_index];
		move.line.push_back(board[new_index_pos.first][new_index_pos.second]);
		move.indexes.push_back(new_index_pos);
		counter--;
	}

	if (shiftVectorByRightIfFoundPlace(move.line)) {
		for (int i = 0; i < move.line.size(); i++) {
			board[move.indexes[i].first][move.indexes[i].second] = move.line[i];
		}
		return true;
	}
	return false;

}

bool Game::handleBottomLeftMovement(Move& move) {
	int counter = move.index + 2;

	while (counter <= move.start_pos.first) {
		std::string new_index = move.starter_letter + std::to_string(counter);
		std::pair<int, int> new_index_pos = board_indexes_map[new_index];
		move.line.push_back(board[new_index_pos.first][new_index_pos.second]);
		move.indexes.push_back(new_index_pos);
		counter++;
	}

	if (shiftVectorByRightIfFoundPlace(move.line)) {
		for (int i = 0; i < move.line.size(); i++) {
			board[move.indexes[i].first][move.indexes[i].second] = move.line[i];
		}
		return true;
	}
	return false;

}

bool Game::handleBottomRightMovement(Move& move) {
	int counter = move.start_pos.second - 1;
	for (int i = move.start_pos.first - 1; i > 0; i--) {
		move.indexes.push_back(std::pair<int, int>(i, counter));
		move.line.push_back(board[i][counter]);
		if (i > game_data.board_size)
			counter--;
	}

	if (shiftVectorByRightIfFoundPlace(move.line)) {
		for (int i = 0; i < move.line.size(); i++) {
			board[move.indexes[i].first][move.indexes[i].second] = move.line[i];
		}
		return true;
	}
	return false;

}

bool Game::checkIfMoveDoesntPushAnyPieceToTheEdge(Move& move) {
	bool wasMoveMade = false;

	if (move.destination_pos.first == move.start_pos.first) {
		wasMoveMade = handleLineMovement(move);
	}
	else {
		//Handle up side of the board
		if (move.start_pos.first <= game_data.board_size) {

			if (move.start_pos.second <= game_data.board_size) {
				wasMoveMade = handleTopLeftMovement(move);
			}

			else {
				wasMoveMade = handleTopRightMovement(move);
			}
		}
		//Handle bottom side of the board
		else {
			if (move.start_pos.second <= game_data.board_size) {
				wasMoveMade = handleBottomLeftMovement(move);
			}
			else {
				wasMoveMade = handleBottomRightMovement(move);
			}
		}
	}

	if (!wasMoveMade) {
		game_status = "BAD_MOVE_ROW_IS_FULL";
		return true;
	}
	else {
		return false;
	}
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
		Move move(start, destination, start_pos, destination_pos);

		if (validateMove(move) && !checkIfMoveDoesntPushAnyPieceToTheEdge(move)) {
			//After placing the piece, remove it from reserve
			if (game_data.current_player == 'B') {
				game_data.reserve_of_black_pieces--;
			}
			else {
				game_data.reserve_of_white_pieces--;
			}

			//Next player's turn
			game_data.current_player = game_data.current_player == 'B' ? 'W' : 'B';

			game_status = "MOVE_COMMITTED";

			validateBoard(true);
		}
	}
	if (game_status != "MOVE_COMMITTED") {
		std::string temp = "bad_move ";
		temp += game_data.current_player;
		temp += ' ';
		game_state = temp + start + '-' + destination;
	}
	std::cout << game_state;
	std::cout << game_status << '\n' << std::endl;
}
