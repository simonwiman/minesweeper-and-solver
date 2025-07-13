#include "backtrack_solver.h"
#include "board.h"
#include <cassert>
#include <set>
#include <utility>

#include <iostream> // debug

typedef struct
{
    int x;
    int y;
    bool flag;
} IndexedBool;

BacktrackSolver::BacktrackSolver(Board* minesweeper_board) : board(minesweeper_board) {}

void BacktrackSolver::solve()
{
    start_solve();

    while( board->get_board_state() == ACTIVE )
    {
        solve_iteration();

        if ( board->game_complete() )
        {
            board->flag_remaining();
            board->set_board_state(COMPLETE);
        }
    }
}

void BacktrackSolver::start_solve()
{
    board->activate_board(board->get_board_height()/2, board->get_board_width()/2);
}

void BacktrackSolver::solve_iteration()
{

    std::vector<std::pair<int, int>> indexes = find_current_choices();
    

    for (int i=0; i < indexes.size(); i++)
    {
        std::cout << indexes[i].first << ", " << indexes[i].second << "\n";
    }
    std::cout << "now for the real deal" << "\n";

    std::set<std::pair<int, int>> visited;
    std::vector<std::vector<std::vector<bool>>> res;

    backtrack(0, indexes, visited, res);
    
    

    std::cout << "size of the vector of templates: " << res.size() << "\n";

}

void BacktrackSolver::backtrack(int n, const std::vector<std::pair<int, int>> &unsolved_tiles, std::set<std::pair<int, int>> &visited_tiles, std::vector<std::vector<std::vector<bool>>> &res)
{
    if ( n == unsolved_tiles.size() )
    {
        std::vector<std::vector<bool>> flag_template = make_flag_template();
        res.push_back(flag_template);

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
            {
                add_adjacent_tiles(i, j, set_of_choices);
            }
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
            {
                set_of_choices.insert(std::pair<int, int>(n, k));
            }
        }
    }
}

bool BacktrackSolver::tile_satisfied(int i, int j) // remove ?, can be good for testing (if you are not an idiot)
{
    int flagged_tiles = 0;
    
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( board->valid_index(n, k) && !((n == i) && (k == j)) && (*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() )
            {
                flagged_tiles++;
            }
        }
    }

    if ( flagged_tiles == (*board->get_tiles())[i][j].get_adjacent_bombs() )
        return true;
    
    if ( flagged_tiles > (*board->get_tiles())[i][j].get_adjacent_bombs() )
        std::cout << "too many flags" << "\n";
    return false;
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

std::vector<std::vector<bool>> BacktrackSolver::make_flag_template()
{
    std::vector<std::vector<bool>> res(board->get_board_height());
    std::vector<std::vector<Tile>> tiles = *board->get_tiles();

    for (int i=0; i < board->get_board_height(); i++)
    {
        std::vector<bool> row(board->get_board_width());

        for (int j=0; j < board->get_board_width(); j++)
        {
            if ( tiles[i][j].get_is_flagged() )
                row.push_back(true);
            else
                row.push_back(false);
        }

        res.push_back(row);
    }

    return res;
}
