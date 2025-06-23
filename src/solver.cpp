#include "solver.h"
#include <cassert>
#include <unordered_map>
#include <utility>

#include <iostream> // for debug


Solver::Solver(Board* minesweeper_board) : board(minesweeper_board) {}

void Solver::solve()
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

void Solver::start_solve()
{
    board->activate_board(board->get_board_height()/2, board->get_board_width()/2);
}

void Solver::solve_iteration()
{
    bool flag_progress = false;
    bool click_progress = false;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            if ( board->game_complete() )
                return;

            assert( !((*board->get_tiles())[i][j].get_is_flagged() && (*board->get_tiles())[i][j].get_is_open()) );

            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() )
            {
                bool current_flag_progress = simple_rule_flag(i, j);
                bool current_click_progress = simple_rule_click(i, j);

                if ( current_flag_progress )
                    flag_progress = true;
                if ( current_click_progress )
                    click_progress = true;
            }
        }
    }

    if ( !flag_progress && !click_progress )
        educated_guess_click();
}

bool Solver::simple_rule_flag(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    int adj_bombs = (*tiles)[i][j].get_adjacent_bombs();
    int possible_bombs = 0;
    int flagged_tiles = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() )
                    possible_bombs++;
                if ( (*tiles)[n][k].get_is_flagged() )
                    flagged_tiles++;
            }
        }
    }

    assert( possible_bombs >= adj_bombs );
    
    if ( possible_bombs == adj_bombs && flagged_tiles != possible_bombs )
    {
        flag_all_adjacent(i , j);
        return true;
    }
        
    return false;
}

void Solver::flag_all_adjacent(int i , int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() && !(*tiles)[n][k].get_is_flagged() )
                    board->place_flag(n, k);
            }
        }
    }
}

bool Solver::simple_rule_click(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    int adj_bombs = (*tiles)[i][j].get_adjacent_bombs();
    int planted_flags = 0;
    int clickable_tiles = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( (*tiles)[n][k].get_is_flagged() )
                    planted_flags++;
                if ( !(*tiles)[n][k].get_is_open() && !(*tiles)[n][k].get_is_flagged() )
                    clickable_tiles++;
            }
        }
    }

    if ( planted_flags == adj_bombs && clickable_tiles )
    {
        click_possible(i, j);
        return true;
    }

    return false;
}

void Solver::click_possible(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() && !(*tiles)[n][k].get_is_flagged() )
                {
                    assert( !(*tiles)[n][k].get_is_bomb() );
                    board->open_tile(n, k);
                }
            }
        }
    }
}

void Solver::educated_guess_click()
{
    std::vector<std::pair<std::pair<int, int>, int>> probabilities;
    std::vector<std::pair<int, int>> unknown_probabilties;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {            
            int clickable;
            int flagged;
            int choices;

            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() )
            {
                clickable = count_adj_clickable(i, j);
                flagged = count_adj_flagged(i, j);
                choices = (*board->get_tiles())[i][j].get_adjacent_bombs() - flagged;

                if ( clickable )
                {
                    probabilities.push_back((std::pair<std::pair<int, int>, int>){(std::pair<int, int>){i, j}, choices/clickable});
                }
            }
            else if ( !(*board->get_tiles())[i][j].get_is_open() && !(*board->get_tiles())[i][j].get_is_flagged() )
            {
                unknown_probabilties.push_back((std::pair<int, int>){i, j});
            }
        }
    }

    if ( probabilities.size() )
    {
        std::pair<std::pair<int, int>, int>* lowest_prob = &probabilities[0];

        for ( std::pair<std::pair<int, int>, int> item : probabilities )
        {
            if ( item.second < (*lowest_prob).second )
            {
                lowest_prob = &item;
            }
        }

        int i = (*lowest_prob).first.first;
        int j = (*lowest_prob).first.second;

        std::pair<int, int> tile = get_first_adj_clickable(i, j);

        board->open_tile(tile.first, tile.second);
    }
    else
    {
        assert( unknown_probabilties.size() ); // (we are doomed)

        int i = unknown_probabilties[0].first;  
        int j = unknown_probabilties[0].second; 

        board->open_tile(i, j);
    }
    
}

int Solver::count_adj_clickable(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();
    int clickable = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() && !(*tiles)[n][k].get_is_flagged() )
                {
                    clickable++;
                }
            }
        }
    }
    return clickable;
}

int Solver::count_adj_flagged(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();
    int flagged = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( (*tiles)[n][k].get_is_flagged() )
                {
                    assert( !(*tiles)[n][k].get_is_open() );
                    flagged++;
                }
            }
        }
    }
    return flagged;
}

std::pair<int, int> Solver::get_first_adj_clickable(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() && !(*tiles)[n][k].get_is_flagged() )
                {
                    return (std::pair<int, int>){n, k};
                }
            }
        }
    }
    throw "no clickable tiles"; // L0L
}
