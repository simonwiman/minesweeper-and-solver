#include "backtrack_solver.h"
#include "board.h"
#include <cassert>
#include <set>
#include <utility>

#include <iostream> // debug


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

    std::set<std::pair<int, int>> indexes = find_current_choices();
    std::set<std::pair<int, int>>::iterator it;

    for (it = indexes.begin(); it != indexes.end(); ++it)
    {
        std::cout << (*it).first << ", " << (*it).second << "\n";
    }
    
}

void BacktrackSolver::backtrack(std::vector<int> choices)
{

}

std::set<std::pair<int, int>> BacktrackSolver::find_current_choices()
{
    std::set<std::pair<int, int>> res;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            assert( !((*board->get_tiles())[i][j].get_is_flagged() && (*board->get_tiles())[i][j].get_is_open()) );

            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() )
            {
                put_adjacent_tiles(res, i, j);
            }
        }
    }
    return res;
}

void BacktrackSolver::put_adjacent_tiles(std::set<std::pair<int, int>> &set, int i, int j)
{
    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( !(*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() && board->valid_index(n, k) && !((n == i) && (k == j)) )
            {
                set.insert( (std::pair<int, int>){n, k} );
            }                
        }
    }
}
