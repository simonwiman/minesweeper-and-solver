#pragma once

#include "board.h"


class Solver
{
public:
    Solver(Board* minesweeper_board);
    void solve();
    void start_solve();
    void solve_iteration();
    bool simple_rules();

private:
    Board* board;

    bool simple_rule_flag(int i, int j);
    void flag_all_adjacent(int i, int j);
    bool simple_rule_click(int i, int j);
    void click_possible(int i, int j);
    void educated_guess_click();
    int count_adj_flagged(int i, int j);
    int count_adj_clickable(int i, int j);
    std::pair<int, int> get_first_adj_clickable(int i, int j);

};
