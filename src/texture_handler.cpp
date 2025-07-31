#include <raylib.h>
#include "texture_handler.h"
#include <cassert>
#include <iostream> // debug

TextureHandler::TextureHandler(int tile_size)
{
    texture_tile_hidden = LoadTexture("assets/textures/tiles/tile_hidden.png");
    texture_tile_bomb = LoadTexture("assets/textures/tiles/tile_bomb.png");
    texture_tile_flag = LoadTexture("assets/textures/tiles/tile_flag.png");
    texture_tile_hovered = LoadTexture("assets/textures/tiles/tile_hovered.png");
    texture_tile_0 = LoadTexture("assets/textures/tiles/tile_0.png");
    texture_tile_1 = LoadTexture("assets/textures/tiles/tile_1.png");
    texture_tile_2 = LoadTexture("assets/textures/tiles/tile_2.png");
    texture_tile_3 = LoadTexture("assets/textures/tiles/tile_3.png");
    texture_tile_4 = LoadTexture("assets/textures/tiles/tile_4.png");
    texture_tile_5 = LoadTexture("assets/textures/tiles/tile_5.png");
    texture_tile_6 = LoadTexture("assets/textures/tiles/tile_6.png");
    texture_tile_7 = LoadTexture("assets/textures/tiles/tile_7.png");
    texture_tile_8 = LoadTexture("assets/textures/tiles/tile_8.png");

    assert((texture_tile_hidden.width == tile_size) && (texture_tile_hidden.height == tile_size));
    assert((texture_tile_bomb.width == tile_size) && (texture_tile_bomb.height == tile_size));
    assert((texture_tile_flag.width == tile_size) && (texture_tile_flag.height == tile_size));
    assert((texture_tile_hovered.width == tile_size) && (texture_tile_hovered.height == tile_size));
    assert((texture_tile_0.width == tile_size) && (texture_tile_0.height == tile_size));
    assert((texture_tile_1.width == tile_size) && (texture_tile_1.height == tile_size));
    assert((texture_tile_2.width == tile_size) && (texture_tile_2.height == tile_size));
    assert((texture_tile_3.width == tile_size) && (texture_tile_3.height == tile_size));
    assert((texture_tile_4.width == tile_size) && (texture_tile_4.height == tile_size));
    assert((texture_tile_5.width == tile_size) && (texture_tile_5.height == tile_size));
    assert((texture_tile_6.width == tile_size) && (texture_tile_6.height == tile_size));
    assert((texture_tile_7.width == tile_size) && (texture_tile_7.height == tile_size));
    assert((texture_tile_8.width == tile_size) && (texture_tile_8.height == tile_size));
}

void TextureHandler::draw_board(std::shared_ptr<Board> board)
{

    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            Rectangle rect = (*tiles)[i][j].get_rect();
            bool is_open = (*tiles)[i][j].get_is_open();
            bool is_flagged = (*tiles)[i][j].get_is_flagged();
            bool is_bomb = (*tiles)[i][j].get_is_bomb();
            bool is_hovered = (*tiles)[i][j].get_is_hovered();
            int adjacent_bombs = (*tiles)[i][j].get_adjacent_bombs();

            // assert( !(is_open && is_flagged) );
            
            if (is_hovered && !is_open && !is_flagged)
            {
                DrawTextureV(texture_tile_hovered, (Vector2){rect.x, rect.y}, WHITE);
            }
            else if (!is_open && !is_flagged)
            {
                DrawTextureV(texture_tile_hidden, (Vector2){rect.x, rect.y}, WHITE);
            }
            else if (is_flagged)
            {
                DrawTextureV(texture_tile_flag, (Vector2){rect.x, rect.y}, WHITE);
            }
            else if (is_open && is_bomb)
            {
                DrawTextureV(texture_tile_bomb, (Vector2){rect.x, rect.y}, WHITE);
            }
            else
            {
                switch (adjacent_bombs)
                {
                    case 0:
                        DrawTextureV(texture_tile_0, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 1:
                        DrawTextureV(texture_tile_1, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 2:
                        DrawTextureV(texture_tile_2, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 3:
                        DrawTextureV(texture_tile_3, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 4:
                        DrawTextureV(texture_tile_4, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 5:
                        DrawTextureV(texture_tile_5, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 6:
                        DrawTextureV(texture_tile_6, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 7:
                        DrawTextureV(texture_tile_7, (Vector2){rect.x, rect.y}, WHITE);
                        break;
                    case 8:
                        DrawTextureV(texture_tile_8, (Vector2){rect.x, rect.y}, WHITE);
                        break;    
                }
            }            
        }
    }
}

void TextureHandler::draw_button(Button* button)
{
    Rectangle rect = button->get_rect();
    Texture2D texture;

    if ( button->get_is_hovered() )
        texture = button->get_texture_hovered();
    else
        texture = button->get_texture_normal();

    DrawTextureV(texture, (Vector2){rect.x, rect.y}, WHITE);
}

void TextureHandler::unload_all_textures()
{
    UnloadTexture(texture_tile_hidden);
    UnloadTexture(texture_tile_bomb);
    UnloadTexture(texture_tile_flag);
    UnloadTexture(texture_tile_hovered);
    UnloadTexture(texture_tile_0);
    UnloadTexture(texture_tile_1);
    UnloadTexture(texture_tile_2);
    UnloadTexture(texture_tile_3);
    UnloadTexture(texture_tile_4);
    UnloadTexture(texture_tile_5);
    UnloadTexture(texture_tile_6);
    UnloadTexture(texture_tile_7);
    UnloadTexture(texture_tile_8);
}

TextureHandler::~TextureHandler()
{
    unload_all_textures();
}
