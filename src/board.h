#pragma once

#include "tile.h"
#include <vector>

typedef enum BoardState { UNACTIVE = 0, ACTIVE, DEAD, COMPLETE } BoardState;

class Board
{
public:
    Board(int size, int height, int width, int nr_of_bombs);
    void init_board(float board_loc_x, float board_loc_y);
    void update_board();
    const int get_tile_size();
    const int get_board_height();
    const int get_board_width();
    BoardState get_board_state();
    void set_board_state(BoardState board_state);
    std::vector<std::vector<Tile>>* get_tiles();
    void place_flag(int i, int j);
    void open_tile(int i, int j);
    void activate_board(int i, int j);
    bool game_complete();
    void flag_remaining();
    bool valid_index(int i, int j);

private:
    const int tile_size;
    const int board_height;
    const int board_width;
    int bombs;
    std::vector<std::vector<Tile>> tiles;
    BoardState board_state;

    void check_clicks();
    void init_bomb_counter(int i, int j);
    void open_adjacent_tiles(int i, int j);
    void open_remaining_bombs();
};
