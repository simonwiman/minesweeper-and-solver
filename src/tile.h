#pragma once

#include <raylib.h>


class Tile
{
public:
    Tile(Rectangle rect, bool is_open, bool is_bomb, bool is_flagged, bool is_held, int adjacent_bombs);
    Rectangle get_rect();
    bool get_is_open();
    bool get_is_bomb();
    bool get_is_flagged();
    bool get_is_held();
    int get_adjacent_bombs();
    void set_adjacent_bombs(int adjacent_bombs);
    void set_is_open(bool is_open);
    void set_is_bomb(bool is_bomb);
    void set_is_flagged(bool is_flagged);
    void set_is_held(bool is_held);
    void update_flagged();

private:
    Rectangle rect;
    bool is_open;
    bool is_bomb;
    bool is_flagged;
    bool is_held;
    int adjacent_bombs;
};
