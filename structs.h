#pragma once
struct GameData {
	int board_size;
	int number_of_pieces_that_trigger_collection_of_pieces;
	int number_of_white_pieces;
	int number_of_black_pieces;
	int reserve_of_white_pieces;
	int reserve_of_black_pieces;
	char starting_player;
};