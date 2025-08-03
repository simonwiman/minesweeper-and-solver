#pragma once

#include "board.h"
#include "solver.h"
#include <set>
#include <memory>
#include "observer.h"


class BacktrackSolver
{
public:
    BacktrackSolver(std::shared_ptr<Board> minesweeper_board);
    void solve();
    void solve_iteration();
    void start_solve();
    void set_board(std::shared_ptr<Board> minesweeper_board);
    void add_observer(Observer*);
    
private:
    std::shared_ptr<Board> board;
    Solver simple_solver;
    std::vector<Observer*> observers;


    void backtrack(std::size_t n, const std::vector<std::pair<int, int>> &unsolved_tiles, std::set<std::pair<int, int>> &visited_tiles, std::vector<std::vector<bool>> &res);
    std::vector<std::pair<int, int>> find_current_choices();
    void add_adjacent_tiles(int i, int j, std::set<std::pair<int, int>> &set_of_choices);
    bool tile_satisfied(int i, int j);
    bool tile_valid(int i, int j, std::set<std::pair<int, int>> &visited_tiles);
    bool adjacent_constraints_check(int i, int j, std::set<std::pair<int, int>> &visited_tiles);
    std::vector<bool> map_flags(const std::vector<std::pair<int, int>> &tiles);
    bool backtrack_iteration();
    void notify_observers();

};
