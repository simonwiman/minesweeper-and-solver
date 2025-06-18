#include "solver.h"
#include <cassert>


Solver::Solver(Board* minesweeper_board) : board(minesweeper_board)
{

    // board = minesweeper_board;
}

void Solver::solve()
{

    start_solve();

    while( board->get_board_state() == ACTIVE )
    {
        solve_iteration();
    }

    // look if we won or lost, handle accordingly

}

void Solver::start_solve()
{
    board->activate_board(10, 10);
}

void Solver::solve_iteration()
{
    bool break_flag = false;

    for (int i=0; i < board->get_board_height(); i++)
    {
        for (int j=0; j < board->get_board_width(); j++)
        {
            if ( (*board->get_tiles())[i][j].get_is_open() && (*board->get_tiles())[i][j].get_adjacent_bombs() )
            {
                simple_rule_flag(i, j);

                if ( simple_rule_click(i, j) )
                {
                    break_flag = true;
                    break;
                }
            }
        }
        if ( break_flag )
            break;
    }
}

void Solver::simple_rule_flag(int i, int j)
{
    std::vector<std::vector<Tile>> *tiles = board->get_tiles();

    int adj_bombs = (*tiles)[i][j].get_adjacent_bombs();
    int possible_bombs = 0;

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( !(*tiles)[n][k].get_is_open() )
                    possible_bombs++;
            }
        }
    }

    assert( possible_bombs >= adj_bombs );

    if ( possible_bombs == adj_bombs )
        flag_all_adjacent(i , j);
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

    for (int n=i-1; n <= i+1; n++)
    {
        for (int k=j-1; k <= j+1; k++)
        {
            if ( (n >= 0) && (n < board->get_board_height()) && (k >= 0) && (k < board->get_board_width()) && !((n == i) && (k == j)) )
            {                
                if ( (*tiles)[n][k].get_is_flagged() )
                    planted_flags++;
            }
        }
    }

    assert( planted_flags <= adj_bombs );

    if ( planted_flags == adj_bombs )
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
                    (*tiles)[n][k].set_is_open(true);
                }
            }
        }
    }
}
