#include "board.h"
#include "mouse_utility.h"
#include <raylib.h>
#include <set>
#include <utility>
#include <cassert>

#include <iostream> // for debug


Board::Board(int size, int height, int width, int nr_of_bombs) : tile_size(size), board_height(height), board_width(width), board_state(UNACTIVE)
{
    if ( height*width - 9 < nr_of_bombs )
    {
        bombs = height*width - 9;
    }
    else
    {
        bombs = nr_of_bombs;
    }
}

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

std::vector<std::vector<Tile>>* Board::get_tiles()
{
    return &tiles;
}

BoardState Board::get_board_state()
{
    return board_state;
}

void Board::init_board()
{
    for (int i=0; i < board_height; i++)
    {
        std::vector<Tile> current_row;

        for (int j=0; j < board_width; j++)
        {
            current_row.push_back((Tile){(Rectangle){(float)j*tile_size, (float)i*tile_size, (float)tile_size, (float)tile_size}, false, false, false, false, 0});
        }

        tiles.push_back(current_row);
    }
}

void Board::update_board()
{
    switch(board_state)
    {
        case UNACTIVE:
            check_clicks();
            break;

        case ACTIVE:
            check_clicks();

            if ( game_complete() )
            {
                flag_remaining();
                board_state = COMPLETE;
            }

            break;

        case DEAD:
            break;

        case COMPLETE:
            break;
    }
}

void Board::check_clicks()
{
    for (int i=0; i < board_height; i++)
    {
        for (int j=0; j < board_width; j++)
        {
            if ( mouse_lclicked_rectangle(tiles[i][j].get_rect()) )
            {
                if (board_state == UNACTIVE)
                {
                    activate_board(i, j);
                    break;
                }
                else
                    open_tile(i, j);
            }
            if ( mouse_rclicked_rectangle(tiles[i][j].get_rect()) )
            {
                place_flag(i, j);
            }
            if ( mouse_overlap_rectangle(tiles[i][j].get_rect()) )
            {
                tiles[i][j].set_is_hovered(true);
            }
            else
            {
                tiles[i][j].set_is_hovered(false);
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

    open_tile(i, j);
}

void Board::init_bomb_counter(int i, int j)
{
    int bomb_counter = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board_height) && (k >= 0) && (k < board_width) && !((n == i) && (k == j)) && tiles[n][k].get_is_bomb() )
            {
                bomb_counter += 1;
            }
        }
    }
    tiles[i][j].set_adjacent_bombs(bomb_counter);
}

void Board::open_adjacent_tiles(int i, int j)
{
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board_height) && (k >= 0) && (k < board_width) && !((n == i) && (k == j)) )
                open_tile(n, k);
        }
    }
}

void Board::open_tile(int i, int j)
{
    Tile* current_tile = &tiles[i][j];

    if ( current_tile->get_is_bomb() && !current_tile->get_is_flagged() )
    {
        assert( !current_tile->get_is_open() );
        current_tile->set_is_open(true);
        board_state = DEAD;
        open_remaining_bombs();
    }
    else if ( !current_tile->get_is_open() && !current_tile->get_is_flagged() )
    {
        current_tile->set_is_open(true);

        if ( !current_tile->get_adjacent_bombs() )
            open_adjacent_tiles(i, j);
    }
}

void Board::place_flag(int i, int j)
{
    if ( !tiles[i][j].get_is_open() )
    {
        tiles[i][j].update_flagged();
    }
}

void Board::open_remaining_bombs()
{
    for (int i=0; i < board_height; i++)
    {
        for (int j=0; j < board_width; j++)
        {
            if ( tiles[i][j].get_is_bomb() )
            {
                tiles[i][j].set_is_open(true);
            }
        }
    }
}

bool Board::game_complete()
{
    for (int i=0; i < board_height; i++)
    {
        for (int j=0; j < board_width; j++)
        {
            if ( !tiles[i][j].get_is_bomb() && !tiles[i][j].get_is_open() )
            {
                return false;
            }
        }
    }
    return true;
}

void Board::flag_remaining()
{
    for (int i=0; i < board_height; i++)
    {
        for (int j=0; j < board_width; j++)
        {
            if ( tiles[i][j].get_is_bomb() )
            {
                tiles[i][j].set_is_flagged(true);
            }
        }
    }
}
