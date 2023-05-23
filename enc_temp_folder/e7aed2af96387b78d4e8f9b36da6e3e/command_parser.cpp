#include "command_parser.h"

void CommandParser::run() {
	std::string input;
	while (std::getline(std::cin, input)) {
		if (input == "LOAD_GAME_BOARD") {
			InputParser new_input_parser;
			new_input_parser.getDataFromUser();
			new_input_parser.getBoardFromUser();
			new_input_parser.validateBoard();
			input_parser = new_input_parser;
		}
	}
}