#pragma once

#include <raylib.h>
#include "board.h"


class TextureHandler {

public:
    void init_textures(int tile_size);
    void draw_board(Board board);
    void unload_all_textures();

private:
    Texture2D texture_tile_hidden;
    Texture2D texture_tile_bomb;
    Texture2D texture_tile_flag;
    Texture2D texture_tile_0;
    Texture2D texture_tile_1;
    Texture2D texture_tile_2;
    Texture2D texture_tile_3;
    Texture2D texture_tile_4;
    Texture2D texture_tile_5;
    Texture2D texture_tile_6;
    Texture2D texture_tile_7;
    Texture2D texture_tile_8;

};
