#pragma once

#include "input_parser.h"
#include "game.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
class CommandParser {
private:
	bool wasGameCreated = false;
	InputParser input_parser;
	Game game;
public:
	CommandParser() {};

	void run();

	~CommandParser() {};
};