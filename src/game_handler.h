#pragma once

#include <cassert>
#include <memory>
#include <array>
#include "backtrack_solver.h"
#include "board.h"
#include "texture_handler.h"
#include "button.h"
#include "timer.h"


class GameHandler : public Observer
{
public:
    GameHandler(int tile_size, int screen_width, int screen_height);
    ~GameHandler();
    void update();
    void reset_board();
    void draw();
    void solve();
    void act_on_update();

    void set_board_width(int width_size);
    void set_board_height(int height_size);
    void set_bombs(int nr_of_bombs);
    

private:
    int tile_size;
    const int screen_width;
    const int screen_height;
    double time_spent;
    int board_width;
    int board_height;
    int bombs;
    std::shared_ptr<Board> board;
    BacktrackSolver solver;
    TextureHandler texture_handler;
    std::array<Button, 6> buttons;
    Timer timer;
    
};
