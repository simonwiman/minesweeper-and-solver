#include <raylib.h>
#include "game_handler.h"

int main()
{    
    const int screen_width  = 1280;
    const int screen_height = 720;
    const int tile_size     = 32;
    
    InitWindow(screen_width, screen_height, "Minesweeper");
    SetTargetFPS(60);
    
    GameHandler game_handler(tile_size, screen_width, screen_height);

    while (!WindowShouldClose())
    {
        game_handler.update();
        game_handler.draw();
    }

    CloseWindow();
}


/*

1. Make gamhandler do solve iterations inbetween frames instead of solving entire board

2. Timer

*/
