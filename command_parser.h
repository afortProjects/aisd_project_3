#pragma once

#include "input_parser.h"

#include <iostream>
#include <string>
class CommandParser {
private:
	InputParser input_parser;
public:
	CommandParser() {};

	void run();

	~CommandParser() {};
};