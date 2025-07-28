#include <iostream>
#include <random>
#include <vector>
module Game;

Game::Game(int difficulty) : difficulty(difficulty), gen(rd())
{
    Game::InitializeBoard();
}

void Game::InitializeBoard()
{
    int rows = 0, cols = 0;
    switch (difficulty)
    {
    case 1:
        rows = 9;
        cols = 9;
        total_mines = 10;
        break;

    case 2:
        rows = 16;
        cols = 16;
        total_mines = 40;
        break;

    case 3:
        rows = 30;
        cols = 16;
        total_mines = 99;
        break;
    }

    std::uniform_int_distribution<> row_distrib(0, rows - 1);
    std::uniform_int_distribution<> col_distrib(0, cols - 1);

    for (int i = 0; i < rows; i++)
    {
        std::vector<int> row(cols, 0);
        board.push_back(row);
    }

    int placed_mines = 0;
    while (placed_mines < total_mines)
    {
        int mine_row = row_distrib(gen);
        int mine_col = col_distrib(gen);

        if (board[mine_row][mine_col] != -1)
        {
            board[mine_row][mine_col] = -1;
            placed_mines++;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << board[i][j] << " ";
        }
    }
}

void Game::Start()
{
    while (true)
    {
        char option;
        std::cout << "Enter 'd' to display the board, 'q' to quit: ";
        std::cin >> option;
    }
}