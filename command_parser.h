#pragma once

#include "input_parser.h"
#include "game.h"

#include <iostream>
#include <string>
#include <sstream>
class CommandParser {
private:
	InputParser input_parser;
	Game game;
public:
	CommandParser() {};

	void run();

	~CommandParser() {};
};