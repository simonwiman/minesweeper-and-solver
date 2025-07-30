#pragma once

#include <raylib.h>
#include <memory>
#include "board.h"
#include "button.h"


class TextureHandler {

public:
    TextureHandler(int tile_size);
    void draw_board(std::shared_ptr<Board> board);
    void draw_button(Button* button);
    ~TextureHandler();

private:
    Texture2D texture_tile_hidden;
    Texture2D texture_tile_bomb;
    Texture2D texture_tile_flag;
    Texture2D texture_tile_hovered;
    Texture2D texture_tile_0;
    Texture2D texture_tile_1;
    Texture2D texture_tile_2;
    Texture2D texture_tile_3;
    Texture2D texture_tile_4;
    Texture2D texture_tile_5;
    Texture2D texture_tile_6;
    Texture2D texture_tile_7;
    Texture2D texture_tile_8;

    void unload_all_textures();

};
