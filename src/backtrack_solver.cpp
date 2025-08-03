#include "backtrack_solver.h"
#include "board.h"
#include <cassert>
#include <set>
#include <utility>


BacktrackSolver::BacktrackSolver(std::shared_ptr<Board> minesweeper_board) : board(minesweeper_board), simple_solver(Solver(minesweeper_board)) {}

void BacktrackSolver::solve()
{
    start_solve();

    while( board->get_board_state() == ACTIVE )
    {
        solve_iteration();
        notify_observers();

        if ( board->game_complete() )
        {
            board->flag_remaining();
            board->set_board_state(COMPLETE);
        }
    }
}

void BacktrackSolver::start_solve()
{
    simple_solver.start_solve();
}

void BacktrackSolver::solve_iteration()
{
    if ( simple_solver.simple_rules() )
        return;
       
    if ( backtrack_iteration() )
        return;

    simple_solver.educated_guess_click();
}

bool BacktrackSolver::backtrack_iteration()
{
    std::vector<std::pair<int, int>> indexes = find_current_choices();
    
    std::set<std::pair<int, int>> visited;
    std::vector<std::vector<bool>> flag_layouts;

    backtrack(0, indexes, visited, flag_layouts);

    for (std::size_t k=0; k < flag_layouts.size() - 1; k++)
    {
        assert(flag_layouts[k].size() == flag_layouts[k+1].size());
    }

    bool progression_made = false;

    for (std::size_t n=0; n < indexes.size(); n++)
    {   
        std::size_t counter = 0;

        for (std::size_t k=0; k < flag_layouts.size(); k++)
        {
            if ( flag_layouts[k][n] )
                counter++;
        }

        if ( counter == flag_layouts.size() ) // flagged in all layouts
        {
            int i = indexes[n].first;
            int j = indexes[n].second;
            (*board->get_tiles())[i][j].set_is_flagged(true);
            progression_made = true;
        }

        else if ( counter == 0 ) // unflagged in all layouts
        {
            int i = indexes[n].first;
            int j = indexes[n].second;
            board->open_tile(i, j);
            progression_made = true;
        }
    }

    return progression_made;
}

void BacktrackSolver::backtrack(std::size_t n, const std::vector<std::pair<int, int>> &unsolved_tiles, std::set<std::pair<int, int>> &visited_tiles, std::vector<std::vector<bool>> &res)
{
    if ( n == unsolved_tiles.size() )
    {
        std::vector<bool> flag_layout = map_flags(unsolved_tiles);
        res.push_back(flag_layout);
        return;
    }

    int i = unsolved_tiles[n].first;
    int j = unsolved_tiles[n].second;
    
    visited_tiles.insert(std::pair<int, int>(i, j));

    (*board->get_tiles())[i][j].set_is_flagged(true);

    if ( adjacent_constraints_check(i, j, visited_tiles) )
    {
        backtrack(n + 1, unsolved_tiles, visited_tiles, res);
    }

    (*board->get_tiles())[i][j].set_is_flagged(false);
    
    if ( adjacent_constraints_check(i, j, visited_tiles) )
    {
        backtrack(n + 1, unsolved_tiles, visited_tiles, res);
    }
    
    visited_tiles.erase(std::pair<int, int>(i, j));
}

std::vector<std::pair<int, int>> BacktrackSolver::find_current_choices()
{
    std::set<std::pair<int, int>> set_of_choices;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            assert( !((*board->get_tiles())[i][j].get_is_flagged() && (*board->get_tiles())[i][j].get_is_open()) );

            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() )
                add_adjacent_tiles(i, j, set_of_choices);
        }
    }

    std::vector<std::pair<int, int>> res(set_of_choices.begin(), set_of_choices.end());   

    return res;
}

void BacktrackSolver::add_adjacent_tiles(int i, int j, std::set<std::pair<int, int>> &set_of_choices)
{
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( board->valid_index(n, k) && !((n == i) && (k == j)) && !(*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() )
                set_of_choices.insert(std::pair<int, int>(n, k));
        }
    }
}

bool BacktrackSolver::tile_valid(int i, int j, std::set<std::pair<int, int>> &visited_tiles)
{
    int flagged_tiles = 0;
    int touchable_unflagged = 0;
    int adjacent_bombs = (*board->get_tiles())[i][j].get_adjacent_bombs();
    
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( board->valid_index(n, k) && !((n == i) && (k == j)) )
            {
                if ( (*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() )
                    flagged_tiles++;

                if ( !(*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() && !visited_tiles.count(std::pair<int, int>(n, k)) )
                    touchable_unflagged++;
            }
        }
    }

    if ( flagged_tiles > adjacent_bombs || touchable_unflagged + flagged_tiles < adjacent_bombs )
        return false;
    return true;
}

bool BacktrackSolver::adjacent_constraints_check(int i, int j, std::set<std::pair<int, int>> &visited_tiles)
{
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( board->valid_index(n, k) && !((n == i) && (k == j)) && (*board->get_tiles())[n][k].get_is_open() && (*board->get_tiles())[n][k].get_adjacent_bombs() )
            {
                if ( !tile_valid(n, k, visited_tiles) )
                    return false;
            }
        }
    }
    return true;
}

std::vector<bool> BacktrackSolver::map_flags(const std::vector<std::pair<int, int>> &tiles)
{
    std::vector<bool> res;

    for (auto index: tiles)
    {
        int i = index.first;
        int j = index.second;
        
        if ( (*board->get_tiles())[i][j].get_is_flagged() )
            res.push_back(true);
        else
            res.push_back(false);
    }

    return res;
}

void BacktrackSolver::set_board(std::shared_ptr<Board> minesweeper_board)
{
    simple_solver.set_board(minesweeper_board);
    board = minesweeper_board;
}

void BacktrackSolver::notify_observers()
{
    for (std::size_t i = 0; i < observers.size(); i++)
        observers[i]->act_on_update();
}

void BacktrackSolver::add_observer(Observer* observer)
{
    observers.push_back(observer);
}
