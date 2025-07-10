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

    // backtrack(indexes);
    
}

void BacktrackSolver::backtrack(int n, const std::vector<std::pair<int, int>> &unsolved_tiles, std::set<std::pair<int, int>> &visited_tiles) // visited_tiles will be saved across usese of backtracking, for one solve
{
    int i;
    int j;

    if ( n == unsolved_tiles.size() )
    {
        // but actually append one answer of confugurations
        return;
    }

    i = unsolved_tiles[n].first;
    j = unsolved_tiles[n].second;
    
    std::cout << i << ", " << j << "\n";



    // we should loop through all the combinations of mines of adjacent tiles, then if valid, backtrack, else do nothing
    // if we backtrack, take the tiles into visited, and remove them from visited afterwards

    std::vector<std::pair<int, int>> adjacent_tiles;

    std::vector<std::vector<std::pair<int, int>>> working_indexes; // = get_working_indexes(i, j)
    
    for (int k=0; k < working_indexes.size(); k++) // this does not work, we have to make sure we dont touch visited and we have to flip the flag instead (could be iffy, think about this more). Everything has to be added to visited, so we need to iterate over the entire 3x3 square
    {
        for (int m=0; m < working_indexes[k].size(); m++)
        {
            int row = working_indexes[k][m].first;
            int column = working_indexes[k][m].second;

            (*board->get_tiles())[row][column].set_is_flagged(true);
            visited_tiles.insert( std::pair<int, int>(row, column) );
        }

        backtrack(n+1, unsolved_tiles, visited_tiles);

        for (int m=0; m < working_indexes[k].size(); m++)
        {
            int row = working_indexes[k][m].first;
            int column = working_indexes[k][m].second;

            (*board->get_tiles())[row][column].set_is_flagged(false);
            visited_tiles.erase( std::pair<int, int>(row, column) );
        }
    }

    

    


}

std::vector<std::pair<int, int>> BacktrackSolver::find_current_choices()
{
    std::vector<std::pair<int, int>> res;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            assert( !((*board->get_tiles())[i][j].get_is_flagged() && (*board->get_tiles())[i][j].get_is_open()) );

            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() && tile_satisfied(i, j) )
            {
                res.push_back( std::pair<int, int>(i, j) );
            }
        }
    }
    return res;
}

bool BacktrackSolver::tile_satisfied(int i, int j)
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
    return false;
}

// std::vector<std::vector<IndexedBool>> BacktrackSolver::get_working_indexes(int i, int j, std::set<std::pair<int, int>> &visited)
// {
//     std::vector<std::vector<IndexedBool>> res;

//     int flagged_tiles = 0;

//     for (int n=i-1; n <= i+1; n++)
//     {
//         for (int k=j-1; k <= j+1; k++)
//         {
//             if ( board->valid_index(n, k) && !((n == i) && (k == j)) && (*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() )
//             {
//                 flagged_tiles++;
//             }
//         }
//     }

//     return res;
// }

// void BacktrackSolver::get_working_indexes_helper(int n, int i, int j, std::set<std::pair<int, int>> &visited, std::vector<std::vector<IndexedBool>> &res)
// {
//     int adjacent_bombs = (*board->get_tiles())[i][j].get_adjacent_bombs();
    
//     const int i_direction[] = {-1, -1, -1,  0, 0,  1, 1, 1};
//     const int j_direction[] = {-1,  0,  1, -1, 1, -1, 0, 1};


//     if ( board->valid_index(i + i_direction[n], j + j_direction[n]) && !visited.count(std::pair<int, int>(i + i_direction[n], j + j_direction[n])) )
//     {
//         (*board->get_tiles())[i + i_direction[n]][j + j_direction[n]].set_is_flagged(true);

//         if ( tile_valid(i, j) )

//     }

// }

// bool BacktrackSolver::tile_valid(int i, int j)
// {

//     int flagged_tiles = 0;
    
//     for (int n=i-1; n <= i+1; n++)
//     {
//         for (int k=j-1; k <= j+1; k++)
//         {
//             if ( board->valid_index(n, k) && !((n == i) && (k == j)) && (*board->get_tiles())[n][k].get_is_flagged() && !(*board->get_tiles())[n][k].get_is_open() )
//             {
//                 flagged_tiles++;
//             }
//         }
//     }

//     if ( flagged_tiles > (*board->get_tiles())[i][j].get_adjacent_bombs() )
//         return false;
//     return true;

// }
