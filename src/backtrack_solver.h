#pragma once

#include "board.h"
#include <set>

class BacktrackSolver
{
public:
    BacktrackSolver(Board* minesweeper_board);
    void solve();
    void solve_iteration();
    void start_solve();
    
private:
    Board* board;

    void backtrack(std::vector<int> choices);
    std::set<std::pair<int, int>> find_current_choices();
    void put_adjacent_tiles(std::set<std::pair<int, int>> &set, int i, int j);

};
