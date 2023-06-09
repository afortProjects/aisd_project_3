#include "command_parser.h"

void CommandParser::run() {
	std::string input;
	while (std::getline(std::cin, input)) {
		if (input == "LOAD_GAME_BOARD") {
			InputParser new_input_parser;
			new_input_parser.getDataFromUser();
			new_input_parser.getBoardFromUser();
			input_parser = new_input_parser;

			// if board is valid -> create Game object
			wasGameCreated = false;
			std::pair<bool, std::string> input_parser_validation = new_input_parser.validateBoard();

			if (input_parser_validation.first) {
				Game new_game{ new_input_parser.getInputedBoard(), new_input_parser.getGameData() };
				game = new_game;
				std::pair<bool, int> game_board_validation = game.validateBoard(false);
				if (!game_board_validation.first) {
					std::string row_word = game_board_validation.second > 1 ? "ROWS" : "ROW";
					std::cout << "ERROR_FOUND_" <<  game_board_validation.second <<"_" << row_word <<"_OF_LENGTH_K\n" << std::endl;
					wasGameCreated = false;
				}
				else {
					std::cout << input_parser_validation.second << '\n' << std::endl;;
					wasGameCreated = true;
				}
			}
			else {
				std::cout << input_parser_validation.second << '\n' << std::endl;;
			}
		}
		else if (input.find("DO_MOVE") != std::string::npos) {
			//Here, stream is created to split string by spaces, so we can retrieve position and destination positions
			std::istringstream iss(input);
			std::vector<std::string> words(
				std::istream_iterator<std::string>{iss},
				std::istream_iterator<std::string>()
			);    

			//Split string by -
			std::istringstream iss_2(words[1]);
			std::vector<std::string> tokens;
			std::string token;

			while (std::getline(iss_2, token, '-')) {
				tokens.push_back(token);
			}
			if (words.size() > 2 && isalpha(words[2][0])) {
				game.doMove(tokens[0], tokens[1], true, words[2][0], words[3], words[4]);
			} else
				game.doMove(tokens[0], tokens[1]);
		}
		else if (input == "IS_GAME_OVER") {
			game.checkIfPlayerLost();
			game.printGameState();
		}
		else if (input == "PRINT_GAME_BOARD") {
			if (wasGameCreated)
				game.printBoard();
			else
				std::cout << "EMPTY_BOARD" << std::endl;
		}
		else if (input == "GEN_ALL_POS_MOV_NUM") {
			std::cout << GameSolver::GEN_ALL_POS_MOV_NUM(&game) << "_UNIQUE_MOVES" << std::endl;
		}
		else if (input == "GEN_ALL_POS_MOV_EXT_NUM") {
			std::cout << GameSolver::GEN_ALL_POS_MOV_EXT_NUM(&game) << "_UNIQUE_MOVES" << std::endl;
		}
	}

}