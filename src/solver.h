#pragma once

#include "board.h"




class Solver
{
public:
    Solver(Board* minesweeper_board);
    void solve();
    void start_solve();
    void solve_iteration();

private:
    Board* board;

    void simple_rule_flag(int i, int j);
    void flag_all_adjacent(int i, int j);
    bool simple_rule_click(int i, int j);
    void click_possible(int i, int j);
    
};
