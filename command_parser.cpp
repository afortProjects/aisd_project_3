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
			if (new_input_parser.validateBoard()) {
				Game new_game{ new_input_parser.getInputedBoard(), new_input_parser.getGameData() };
				game = new_game;
			}
		}
	}
}