#include <raylib.h>
#include "mouse_utility.h"
#include "tile.h"
#include "board.h"
#include "texture_handler.h"
#include <iostream> // for debug
#include <cassert>


int main()
{
    const Color dark_green = {20, 160, 133, 255};
    
    const int screen_width = 960;
    const int screen_height = 512;
    const int tile_size = 32;

    InitWindow(screen_width, screen_height, "Minesweeper");
    SetTargetFPS(60);
    
    TextureHandler texture_handler;
    Board board(tile_size, 16, 30, 99);

    board.init_board();
    texture_handler.init_textures(tile_size);

    while (!WindowShouldClose())
    {
        board.update_board();
        
        BeginDrawing();

            ClearBackground(dark_green);
            texture_handler.draw_board(board);
                    
        EndDrawing();
    }

    // Cleanup
    texture_handler.unload_all_textures();
    
    CloseWindow();
}
