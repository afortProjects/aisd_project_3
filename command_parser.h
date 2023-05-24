#pragma once

#include "input_parser.h"
#include "game.h"
#include "printing_functions.h"

#include <iostream>
#include <string>
class CommandParser {
private:
	InputParser input_parser;
	Game game;
public:
	CommandParser() {};

	void run();

	~CommandParser() {};
};