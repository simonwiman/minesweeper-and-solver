#include <raylib.h>
#include "mouse_utility.h"
#include "tile.h"
#include "board.h"
#include "texture_handler.h"
#include "solver.h"
#include "backtrack_solver.h"
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


    // L0000L

    BacktrackSolver bsolver(&board);

    bsolver.start_solve();

    BeginDrawing();

        ClearBackground(dark_green);
        texture_handler.draw_board(&board);
            
    EndDrawing();

    bsolver.solve_iteration();
    std::cout << "done lol" << "\n";

    BeginDrawing();

        ClearBackground(dark_green);
        texture_handler.draw_board(&board);
            
    EndDrawing();

    while (true) {}

    // L0000L


    // Solver solver(&board);

    // solver.start_solve();

    // // L0L
    // int completed = 0;
    
    // for (int i=0; i < 100; i++)
    // {
    //     Board board(tile_size, 16, 30, 99);
    //     board.init_board();

    //     Solver solver(&board);

    //     solver.solve();
        
    //     if ( board.get_board_state() == COMPLETE )
    //     {
    //         completed++;
    //     }

    //     BeginDrawing();

    //         ClearBackground(dark_green);
    //         texture_handler.draw_board(&board);
                
    //     EndDrawing();
    // }

    // std::cout << "Completed boards: " << completed << "\n";
    // L0L


    // while (!WindowShouldClose())
    // {
    //     board.update_board();
        
    //     // if ( board.game_complete() )
    //     // {
    //     //     board.flag_remaining();
    //     //     board.set_board_state(COMPLETE);
    //     // }

    //     // if ( board.get_board_state() != DEAD )
    //     //     solver.solve_iteration();

    //     BeginDrawing();

    //         ClearBackground(dark_green);
    //         texture_handler.draw_board(&board);
                    
    //     EndDrawing();

        
    //     // std::cout << COMPLETE << "\n";

    // }

    // Cleanup
    texture_handler.unload_all_textures();
    
    CloseWindow();
}
