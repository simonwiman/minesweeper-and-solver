#include <cassert>
#include <memory>
#include "backtrack_solver.h"
#include "board.h"

#include <iostream>


class GameHandler
{
public:
    GameHandler(int tile_size);
    void update();
    void reset_board();
    void set_board_width(int width_size);
    void set_board_height(int height_size);
    void set_bombs(int nr_of_bombs);


private:
    int tile_size;
    std::shared_ptr<Board> board;
    BacktrackSolver solver;
    double time_spent;
    int board_width;
    int board_height;
    int bombs;
    
};
