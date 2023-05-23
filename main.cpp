#include <iostream>
#include "input_parser.h"
int main() {
	InputParser input_parser;
	input_parser.getDataFromUser();
	input_parser.getBoardFromUser();

	input_parser.printUserBoard();
	input_parser.printUserData();
	return 0;
}