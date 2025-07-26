#include <raylib.h>
#include "mouse_utility.h"
#include "tile.h"
#include "board.h"
#include "texture_handler.h"
#include "solver.h"
#include "backtrack_solver.h"
#include <iostream> // for debug
#include <cassert>
#include <memory>


int main()
{
    const Color dark_green = {20, 160, 133, 255};
    
    const int screen_width = 1280;
    const int screen_height = 720;
    const int tile_size = 32;
    int board_width = 30;
    int board_height = 16;
    int bombs = 99;

    InitWindow(screen_width, screen_height, "Minesweeper");
    SetTargetFPS(60);
    
    TextureHandler texture_handler(tile_size);
    std::shared_ptr<Board> board = std::make_shared<Board>(tile_size, board_height, board_width, bombs);
    board->init_board(screen_width/2 - tile_size*board_width/2, screen_height/2 - board_height*tile_size/2);


    // L0000L

    BacktrackSolver bsolver(board);
    bsolver.start_solve();

    double time_to_start = GetTime();

    while (!WindowShouldClose())
    {

        // if ( IsKeyReleased(KEY_F) )
        //     bsolver.solve_iteration();

        if ( board->game_complete() )
        {
            board->flag_remaining();
            board->set_board_state(COMPLETE);
            std::cout << "time: " << GetTime() - time_to_start << "\n";
            break;
        }

        if ( board->get_board_state() != DEAD )
            bsolver.solve_iteration();


        BeginDrawing();
            ClearBackground(dark_green);
            texture_handler.draw_board(board);
        EndDrawing();
    }

    // L0000L




    // // L0L
    // int completed = 0;
    
    // for (int i=0; i < 20; i++)
    // {
    //     Board board(tile_size, 16, 30, 99);
    //     board.init_board();

    //     BacktrackSolver bsolver(&board);

    //     bsolver.solve();
        
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
    
    CloseWindow();
}
