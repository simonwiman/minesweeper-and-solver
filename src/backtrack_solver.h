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

    void backtrack(int n, const std::vector<std::pair<int, int>> &unsolved_tiles, std::set<std::pair<int, int>> &visited_tiles);
    std::vector<std::pair<int, int>> find_current_choices();
    bool tile_satisfied(int i, int j);
    std::vector<std::vector<IndexedBool>> get_working_indexes(int i, int j, std::set<std::pair<int, int>> &visited);
    void get_working_indexes_helper(int n, int i, int j, std::set<std::pair<int, int>> &visited, std::vector<std::vector<IndexedBool>> res);
    bool tile_valid(int i, int j);

};
