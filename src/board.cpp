#include "board.h"
#include "mouse_utility.h"
#include <raylib.h>

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
                // if they were, reveal that tile ()

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
                activate_board(i, j);
                break;
            }
        }
    }
}

void Board::activate_board(int i, int j)
{
    board_state = ACTIVE;
 
    std::cout << "board activated, tile pressed: " << i << ", " << j << "\n";

    /* Idea 1
    create a vector of length:(board_height*board_length - 9)
    the vector should have bombs amount of zeroes in it, and 
    iterate over the board, initialize the tiles based on the vector, simply skip the vector (and don't increment it) if it is one of the key tiles
    */
    
    /* Idea 2
    
    keep count of how many bombs must be distributed

    keep a pool of the indexes (if one unique index combination is picked, you can't pick it again) (can do this with a unordered map)

    can make the nine beggining tiles included in the map

    randomly pick indexes that are allowed, make that a bomb tile

    when no bombs left to distribute, go through the rest of the tiles to initialzie them
    
    */


}
