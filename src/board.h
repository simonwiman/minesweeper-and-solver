#pragma once

#include "tile.h"
#include <vector>

typedef enum BoardState { UNACTIVE = 0, ACTIVE, DEAD } BoardState;

class Board
{
public:
    Board(int size, int height, int width, int nr_of_bombs);
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
    const int bombs;
    std::vector<std::vector<Tile>> tiles;
    BoardState board_state;

    void activate_board(int i, int j);
    void check_to_init();
};
