#include "board.h"
#include "mouse_utility.h"
#include <raylib.h>
#include <set>
#include <utility>
#include <cassert>

#include <iostream> // for debug


Board::Board(int size, int height, int width, int nr_of_bombs) : tile_size(size), board_height(height), board_width(width), bombs(nr_of_bombs), board_state(UNACTIVE) {}

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
    return board_width;
}

std::vector<std::vector<Tile>> Board::get_tiles()
{
    return tiles;
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

        tiles.push_back(current_row);
    }

}

void Board::update_board()
{
    
    switch(board_state)
    {
        case UNACTIVE:
            check_to_init();
            break;

        case ACTIVE:
            
        // check if any tiles were clicked
                // if they were, reveal that tile (bomb counter should already be accurate, so only reveal and let the texture handler draw it)

            break;

        case DEAD:

            // do not check the tiles, keep state (on death, update the board once accordingly)
            
            break;
    }

}

void Board::check_to_init()
{
    for (int i=0; i < board_height; i++)
    {
        for (int j=0; j < board_width; j++)
        {
            if ( mouse_clicked_rectangle(tiles[i][j].get_rect()) )
            {
                tiles[i][j].set_is_open(true);

                activate_board(i, j);
                break;
            }
        }
    }
}

void Board::activate_board(int i, int j)
{
    board_state = ACTIVE;
 
    std::set<std::pair<int, int>> occupied_indexes;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board_height) && (k >= 0) && (k < board_width) )
            {
                occupied_indexes.insert( (std::pair<int, int>){n, k} );
                tiles[n][k].set_is_open(true);
            }
        }
    }

    int bombs_left = bombs;
    int rand_i;
    int rand_j;

    while (bombs_left > 0)
    {
        rand_i = GetRandomValue(0, board_height - 1);
        rand_j = GetRandomValue(0, board_width - 1);

        std::pair<int, int> bomb_try(rand_i, rand_j);

        if ( !occupied_indexes.count(bomb_try) )
        {
            occupied_indexes.insert(bomb_try);
            tiles[rand_i][rand_j].set_is_bomb(true);
            bombs_left -= 1;
        }
    }

    for (int n=0; n < board_height; n++)
    {
        for (int k=0; k < board_width; k++)
        {
            init_bomb_counter(n, k);
        }
    }

}

void Board::init_bomb_counter(int i, int j)
{
    int bomb_counter = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board_height) && (k >= 0) && (k < board_width) && !((n == i) && (n == j)) && tiles[n][k].get_is_bomb() ) // maybe refactor out of bounds part
            {
                bomb_counter += 1;
            }
        }
    }
    tiles[i][j].set_adjacent_bombs(bomb_counter);
}
