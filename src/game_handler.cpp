#include <cassert>
#include "game_handler.h"

#include <iostream>


GameHandler::GameHandler(int tile_size, int screen_width, int screen_height) : tile_size(tile_size), screen_width(screen_width), screen_height(screen_height), time_spent(0), board_width(30), board_height(16), bombs(99), board(std::make_shared<Board>(tile_size, board_height, board_width, bombs)), solver(BacktrackSolver(board)), texture_handler(TextureHandler(tile_size))
{
    const int first_tile_x_position = screen_width/2 - tile_size*board_width/2;
    const int first_tile_y_position = screen_height/2 - board_height*tile_size/2;

    board->init_board(first_tile_x_position, first_tile_y_position);

    Texture2D texture_normal = LoadTexture("assets/textures/button_normal.png");
    Texture2D texture_hovered = LoadTexture("assets/textures/button_hovered.png");

    std::function<void()> on_click_reset = [this]() { this->reset_board(); };
    std::function<void()> on_click_solve = [this]() { this->solve(); };
    std::function<void()> on_click_diff_easy = [this]() {
        this->set_board_height(9);
        this->set_board_width(9);
        this->set_bombs(10);
        this->reset_board();
    };
    std::function<void()> on_click_diff_medium = [this]() {
        this->set_board_height(16);
        this->set_board_width(16);
        this->set_bombs(40);
        this->reset_board();
    };
    std::function<void()> on_click_diff_expert = [this]() {
        this->set_board_height(16);
        this->set_board_width(30);
        this->set_bombs(99);
        this->reset_board();
    };
    std::function<void()> on_click_diff_master = [this]() {
        this->set_board_height(20);
        this->set_board_width(30);
        this->set_bombs(145);
        this->reset_board();
    };

    Button reset_button( on_click_reset, texture_normal, texture_hovered, (Rectangle){0, 0, 32, 16} );
    Button solve_button( on_click_solve, texture_normal, texture_hovered, (Rectangle){50, 10, 32, 16} );
    Button diff_easy_button( on_click_diff_easy, texture_normal, texture_hovered, (Rectangle){90, 10, 32, 16} );
    Button diff_medium_button( on_click_diff_medium, texture_normal, texture_hovered, (Rectangle){130, 10, 32, 16} );
    Button diff_expert_button( on_click_diff_expert, texture_normal, texture_hovered, (Rectangle){170, 10, 32, 16} );
    Button diff_master_button( on_click_diff_master, texture_normal, texture_hovered, (Rectangle){220, 10, 32, 16} );

    buttons = {reset_button, solve_button, diff_easy_button, diff_medium_button, diff_expert_button, diff_master_button};
}

void GameHandler::update()
{
    board->update_board();

    for (std::size_t i=0; i < buttons.size(); i++)
    {
        buttons[i].update();
    }
}

void GameHandler::reset_board()
{
    std::shared_ptr<Board> new_board = std::make_shared<Board>(tile_size, board_height, board_width, bombs);
    board = new_board;

    const int first_tile_x_position = screen_width/2 - tile_size*board_width/2;
    const int first_tile_y_position = screen_height/2 - board_height*tile_size/2;
    
    board->init_board(first_tile_x_position, first_tile_y_position);
    solver.set_board(new_board);
}

void GameHandler::draw()
{
    const Color dark_green = {20, 160, 133, 255};

    BeginDrawing();

        ClearBackground(dark_green);
        texture_handler.draw_board(board);
        
        for (std::size_t i=0; i < buttons.size(); i++)
        {
            texture_handler.draw_button(&buttons[i]);
        }

    EndDrawing();
}

void GameHandler::solve()
{
    // but we actually need to go into a different state and do iterations, so that we can see real-time solving
}

void GameHandler::set_board_width(int width_size)
{
    board_width = width_size;
}

void GameHandler::set_board_height(int height_size)
{
    board_height = height_size;
}

void GameHandler::set_bombs(int nr_of_bombs)
{
    bombs = nr_of_bombs;
}
