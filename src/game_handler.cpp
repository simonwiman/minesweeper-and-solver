#include <cassert>
#include "game_handler.h"

#include <iostream>


GameHandler::GameHandler(int tile_size) : tile_size(tile_size), time_spent(0), board_width(30), board_height(16), bombs(99), board(std::make_shared<Board>(tile_size, board_height, board_width, bombs)), solver(BacktrackSolver(board)) {}

void GameHandler::update()
{

}

void GameHandler::reset_board()
{
    std::shared_ptr<Board> new_board = std::make_shared<Board>(tile_size, board_height, board_width, bombs);
    board = new_board;
    solver.set_board(new_board);
}

void GameHandler::draw()
{

}

void GameHandler::set_board_width(int width_size)
{
    board_width = width_size;
}

void GameHandler::set_board_height(int height_size)
{
    board_height = height_size;
}

void GameHandler::set_bombs(int nr_of_bombs)
{
    bombs = nr_of_bombs;
}
