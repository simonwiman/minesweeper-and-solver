#include <cassert>
#include "game_handler.h"

#include <iostream>


GameHandler::GameHandler(int tile_size, int screen_width, int screen_height) : tile_size(tile_size), screen_width(screen_width), screen_height(screen_height), time_spent(0), board_width(30), board_height(16), bombs(99), board(std::make_shared<Board>(tile_size, board_height, board_width, bombs)), solver(BacktrackSolver(board)), texture_handler(TextureHandler(tile_size))
{
    board->init_board(screen_width/2 - tile_size*board_width/2, screen_height/2 - board_height*tile_size/2);
}

void GameHandler::update()
{
    board->update_board();

    // add: update all buttons
}

void GameHandler::reset_board()
{
    std::shared_ptr<Board> new_board = std::make_shared<Board>(tile_size, board_height, board_width, bombs);
    board = new_board;
    solver.set_board(new_board);
}

void GameHandler::draw()
{
    texture_handler.draw_board(board);

    // add: draw buttons
    // add: draw extra stuff
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
