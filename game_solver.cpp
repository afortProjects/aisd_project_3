#include "game_solver.h"

bool GameSolver::is_board_unique(const std::vector<std::vector<char>>& target, const std::vector<std::vector<std::vector<char>>>& container) {
	 for (const auto& element : container) {
		 if (element == target) {
			 return false;
		 }
	 }
	 return true;
}

int GameSolver::GEN_ALL_POS_MOV_NUM(Game* game) {
	// We substract 1, because that's the base state
	int size = GEN_ALL_POS_MOV(game).size();
	return size;
}

std::vector<std::vector<std::vector<char>>> GameSolver::GEN_ALL_POS_MOV(Game* game) {
	std::vector<std::vector<std::vector<char>>> unique_boards;
	std::vector<Game> unique_games;
	
	//Check all possible moves, if generated board is unique add it to unique_boards vector

	for (int i = 1; i < game->board.size()-1; i++) {
		for (int j = 0; j < game->board[i].size(); j++) {
			if (game->board[i][j] != ' ') {
				Game new_game = game->doMoveForSolver(std::pair<int, int> {i, j}, std::pair<int, int> {i, j + 1});
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);
				}
				if (i < game->game_data.board_size) {
					new_game = game->doMoveForSolver(std::pair<int, int> {i, j}, std::pair<int, int> {i + 1, j});
					if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
						unique_boards.push_back(new_game.board);
						unique_games.push_back(new_game);
					}
				}
				else if (i > game->game_data.board_size) {
					new_game = game->doMoveForSolver(std::pair<int, int> {i, j}, std::pair<int, int> {i - 1, j});
					if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
						unique_boards.push_back(new_game.board);
						unique_games.push_back(new_game);

					}
				}
				break;
			}	
		}

		Game new_game = game->doMoveForSolver(std::pair<int, int> {i, game->board[i].size()-1}, std::pair<int, int> {i, game->board[i].size()-2});
		if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
 			unique_boards.push_back(new_game.board);
			unique_games.push_back(new_game);

		}
		if (i < game->game_data.board_size) {
			new_game = game->doMoveForSolver(std::pair<int, int> {i, game->board[i].size() - 1}, std::pair<int, int> {i + 1, game->board[i].size() - 2});
			if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
				unique_boards.push_back(new_game.board);
				unique_games.push_back(new_game);

			}
		}
		else if (i > game->game_data.board_size) {
			new_game = game->doMoveForSolver(std::pair<int, int> {i, game->board[i].size() - 1}, std::pair<int, int> {i - 1, game->board[i].size() - 2});
			if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
				unique_boards.push_back(new_game.board);
				unique_games.push_back(new_game);

			}
		}

	}

	//Handle first row
	for (int i = 0; i < game->board[0].size(); i++) {
		if (game->board[0][i] != ' ') {
			std::pair<int, int> start, stop;
			if (i == game->game_data.board_size || i == game->game_data.board_size * 2) {
				start.first = 0;
				start.second = i;
				stop.first = 1;
				stop.second = i == game->game_data.board_size ? i : i-1;
				Game new_game = game->doMoveForSolver(start, stop);
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}
			}
			else {
				Game new_game = game->doMoveForSolver(std::pair<int, int> {0, i}, std::pair<int, int> {1, i-1});
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}

				new_game = game->doMoveForSolver(std::pair<int, int> {0, i}, std::pair<int, int> {1, i});
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}
			}
		}
	}

	//Handle last row
	for (int i = 0; i < game->board[game->game_data.board_size*2].size(); i++) {
		std::pair<int, int> start, stop;
		if (game->board[game->game_data.board_size * 2][i] != ' ') {
			if (i == game->game_data.board_size || i == game->game_data.board_size * 2) {
				start.first = game->game_data.board_size * 2;
				start.second = i;
				stop.first = game->game_data.board_size * 2 - 1;
				stop.second = i == game->game_data.board_size * 2 ? i - 1 : i;
				Game new_game = game->doMoveForSolver(start, stop);
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}
			}
			else {
				Game new_game = game->doMoveForSolver(std::pair<int, int> {game->game_data.board_size * 2, i}, std::pair<int, int> {game->game_data.board_size * 2 - 1, i - 1});
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}	

				new_game = game->doMoveForSolver(std::pair<int, int> {game->game_data.board_size*2, i}, std::pair<int, int> {game->game_data.board_size * 2 - 1, i});
				if (is_board_unique(new_game.board, unique_boards) && new_game.board != game->board) {
					unique_boards.push_back(new_game.board);
					unique_games.push_back(new_game);

				}
			}
		}
	}
	/*for (auto& board : unique_boards) {
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
	}*/

	//for (auto& game : unique_games) {
	//	game.printBoard();
	//}
	return unique_boards;
}