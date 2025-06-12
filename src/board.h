#pragma once

#include "tile.h"
#include <vector>

class Board
{

public:
    Board(int size, int height, int width);
    void init_board();
    void update_board();
    const int get_tile_size();
    const int get_board_height();
    const int get_board_width();
    std::vector<std::vector<Tile>> get_tiles();

private:
    const int tile_size;
    const int board_height;
    const int board_width;
    std::vector<std::vector<Tile>> tiles;

};
