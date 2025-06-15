#include "tile.h"
#include <raylib.h>
#include <cassert>


Tile::Tile(Rectangle rect, bool is_open, bool is_bomb, bool is_flagged, int adjacent_bombs)
{
    assert( !(is_open && is_flagged) );
    
    this->rect = rect;
    this->is_open = is_open;
    this->is_bomb = is_bomb;
    this->is_flagged = is_flagged;
    this->adjacent_bombs = adjacent_bombs;
}

Rectangle Tile::get_rect()
{
    return rect;
}

bool Tile::get_is_open()
{
    return is_open;
}

bool Tile::get_is_bomb()
{
    return is_bomb;
}

bool Tile::get_is_flagged()
{
    return is_bomb;
}

int Tile::get_adjacent_bombs()
{
    return is_bomb;
}

void Tile::set_adjacent_bombs(int adjacent_bombs)
{
    this->adjacent_bombs = adjacent_bombs;
}

void Tile::set_is_open(bool is_open)
{
    this->is_open = is_open;
}

void Tile::set_is_bomb(bool is_bomb)
{
    this->is_bomb = is_bomb;
}

void Tile::set_is_flagged(bool is_flagged)
{
    this->is_flagged = is_flagged;
}
