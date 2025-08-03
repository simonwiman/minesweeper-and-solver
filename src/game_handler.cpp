#include <cassert>
#include "game_handler.h"

#include <iostream>


GameHandler::GameHandler(int tile_size, int screen_width, int screen_height) : tile_size(tile_size), screen_width(screen_width), screen_height(screen_height), time_spent(0), board_width(30), board_height(16), bombs(99), board(std::make_shared<Board>(tile_size, board_height, board_width, bombs)), solver(BacktrackSolver(board)), texture_handler(TextureHandler(tile_size)), timer(Timer())
{
    const int first_tile_x_position = screen_width/2 - tile_size*board_width/2;
    const int first_tile_y_position = screen_height/2 - board_height*tile_size/2;

    board->init_board(first_tile_x_position, first_tile_y_position);
    board->add_observer(&timer);

    solver.add_observer(this);

    Texture2D texture_normal_reset   = LoadTexture("assets/textures/buttons/button_normal_reset.png");
    Texture2D texture_hovered_reset  = LoadTexture("assets/textures/buttons/button_hovered_reset.png");
    Texture2D texture_normal_solve   = LoadTexture("assets/textures/buttons/button_normal_solve.png");
    Texture2D texture_hovered_solve  = LoadTexture("assets/textures/buttons/button_hovered_solve.png");
    Texture2D texture_normal_easy    = LoadTexture("assets/textures/buttons/button_normal_easy.png");
    Texture2D texture_hovered_easy   = LoadTexture("assets/textures/buttons/button_hovered_easy.png");
    Texture2D texture_normal_medium  = LoadTexture("assets/textures/buttons/button_normal_medium.png");
    Texture2D texture_hovered_medium = LoadTexture("assets/textures/buttons/button_hovered_medium.png");
    Texture2D texture_normal_expert  = LoadTexture("assets/textures/buttons/button_normal_expert.png");
    Texture2D texture_hovered_expert = LoadTexture("assets/textures/buttons/button_hovered_expert.png");
    Texture2D texture_normal_master  = LoadTexture("assets/textures/buttons/button_normal_master.png");
    Texture2D texture_hovered_master = LoadTexture("assets/textures/buttons/button_hovered_master.png");

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

    Button reset_button( on_click_reset, texture_normal_reset, texture_hovered_reset, (Rectangle){64, 200, 32, 16} );
    Button solve_button( on_click_solve, texture_normal_solve, texture_hovered_solve, (Rectangle){64, 250, 32, 16} );
    Button diff_easy_button( on_click_diff_easy, texture_normal_easy, texture_hovered_easy, (Rectangle){64, 300, 32, 16} );
    Button diff_medium_button( on_click_diff_medium, texture_normal_medium, texture_hovered_medium, (Rectangle){64, 350, 32, 16} );
    Button diff_expert_button( on_click_diff_expert, texture_normal_expert, texture_hovered_expert, (Rectangle){64, 400, 32, 16} );
    Button diff_master_button( on_click_diff_master, texture_normal_master, texture_hovered_master, (Rectangle){64, 450, 32, 16} );

    buttons = {reset_button, solve_button, diff_easy_button, diff_medium_button, diff_expert_button, diff_master_button};
}

void GameHandler::update()
{
    board->update_board();

    for (std::size_t i=0; i < buttons.size(); i++)
    {
        buttons[i].update();
    }

    if ( board->get_board_state() == ACTIVE )
        timer.update_time();
}

void GameHandler::reset_board()
{
    std::shared_ptr<Board> new_board = std::make_shared<Board>(tile_size, board_height, board_width, bombs);
    board = new_board;

    const int first_tile_x_position = screen_width/2 - tile_size*board_width/2;
    const int first_tile_y_position = screen_height/2 - board_height*tile_size/2;
    
    board->init_board(first_tile_x_position, first_tile_y_position);
    board->add_observer(&timer);
    solver.set_board(new_board);

    timer.reset_time();
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

    DrawText(TextFormat("%03.0f", timer.get_current_time()), 64, 150, 25, RED);
}

void GameHandler::solve()
{
    solver.solve();
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

void GameHandler::act_on_update()
{
    timer.update_time();
    draw();
}

GameHandler::~GameHandler()
{
    for (std::size_t i=0; i < buttons.size(); i++)
        buttons[i].unload_textures();
}
