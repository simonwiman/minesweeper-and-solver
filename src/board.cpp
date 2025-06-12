#include "board.h"
#include <raylib.h>


Board::Board(int size, int height, int width) : tile_size(size), board_height(height), board_width(width) {}

const int Board::get_tile_size()
{
    return this->tile_size;
}

const int Board::get_board_height()
{
    return this->board_height;
}

const int Board::get_board_width()
{
    return this->board_width;
}

std::vector<std::vector<Tile>> Board::get_tiles()
{
    return this->tiles;
}

void Board::init_board()
{

    for (int i=0; i < board_height; i++)
    {
        std::vector<Tile> current_row;

        for (int j=0; j < board_width; j++)
        {
            current_row.push_back((Tile){(Rectangle){(float)j*tile_size, (float)i*tile_size, (float)tile_size, (float)tile_size}, false, false, false, 0});
        }

        this->tiles.push_back(current_row);
    }

}

void Board::update_board()
{

}

/*
Next:

    Handle initialization of board (should do this before handling the regular logic i assume)

        1. Randomlly init board on click

        2. Two states

            1. Before click (all closed, don't care about adjacent bombs, e.t.c)

            2. After click (on click, initialize the board, with the clicked tile initialized as a 0 (that is, that tile and all adjacent tiles are not bombs))

*/
