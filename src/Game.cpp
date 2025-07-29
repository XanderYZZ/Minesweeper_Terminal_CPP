#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <string_view>
import TextColors;

module Game;

Game::Game() : gen(rd()), difficulty(-1) // Initialize the random number generator and set the difficulty to an invalid state
{
    this->PromptForDifficulty();
    this->InitializeBoard();
}

void Game::PromptForDifficulty()
{
    while (difficulty < 1 || difficulty > 3)
    {
        std::cout << std::string(WHITE) + "Select the difficulty level for the game:\n1. Easy\n2. Medium\n3. Hard\nEnter your choice (1-3): ";
        std::cin >> difficulty;

        if (difficulty < 1 || difficulty > 3)
        {
            std::cout << std::string(RED) + "Invalid choice. Please select a valid difficulty level.\n\n";
        }
    }
}

void Game::InitializeBoard()
{
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

    for (int i = 0; i < rows; i++)
    {
        std::vector<Cell> row;
        for (int j = 0; j < cols; j++)
        {
            row.emplace_back(i, j);
        }
        board.push_back(std::move(row));
    }

    this->PlaceMines();
    this->PutAdjacentCounts();
}

void Game::PlaceMines()
{
    std::uniform_int_distribution<> row_distrib(0, rows - 1);
    std::uniform_int_distribution<> col_distrib(0, cols - 1);

    int placed_mines = 0;
    while (placed_mines < total_mines)
    {
        int mine_row = row_distrib(gen);
        int mine_col = col_distrib(gen);

        if (!board[mine_row][mine_col].is_mine)
        {
            board[mine_row][mine_col].is_mine = true;
            placed_mines++;
        }
    }
}

void Game::PutAdjacentCounts()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j].is_mine)
            {
                continue;
            }

            int mine_count = 0;

            for (const auto &direction : directions)
            {
                int new_row = i + direction[0];
                int new_col = j + direction[1];

                if (new_row < 0 || new_col < 0 || new_row >= rows || new_col >= cols)
                {
                    continue;
                }
                if (!board[new_row][new_col].is_mine)
                {
                    continue;
                }

                mine_count++;
            }

            board[i][j].adjacent_mines = mine_count;
        }
    }
}

void Game::DisplayBoard()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::string display = "";

            struct Cell &cell = board[i][j];

            if (!cell.is_revealed)
            {
                display = std::string(GRAY) + "X";
            }
            else
            {
                if (!cell.is_mine)
                {
                    display = cell.adjacent_mines > 0 ? std::string(YELLOW) + std::to_string(cell.adjacent_mines) : std::string(GREEN) + "0";
                }
                else
                {
                    display = std::string(RED) + "*";
                }
            }

            std::cout << display << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

void Game::Start()
{
    this->DisplayBoard(); // Display the initial board, but don't do it inside of the while loop.

    while (true)
    {
        int row = 0, col = 0;

        while (true)
        {
            std::pair<int, int> pair_result = this->GetRowAndCol();
            row = pair_result.first;
            col = pair_result.second;

            struct Cell &cell = board[row][col];

            if (!cell.is_revealed)
            {
                break;
            }
            else
            {
                std::cout << std::string(RED) + "Cell already revealed. Please choose another cell.\n\n";
            }
        }

        struct Cell &cell = board[row][col];
        cell.is_revealed = true;
        if (cell.is_mine)
        {
            this->RevealAllMines();
            this->DisplayBoard();

            std::cout << std::string(RED) + "Game Over! You hit a mine.\n";

            break;
        }
        else
        {
            if (cell.adjacent_mines == 0)
            {
                this->RevealAdjacentCells(row, col);
            }

            this->DisplayBoard();

            if (this->CheckWinCondition())
            {
                std::cout << std::string(GREEN) + "Congratulations! You've cleared the board.\n";

                break;
            }
        }
    }
}

void Game::RevealAllMines()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!board[i][j].is_mine)
            {
                continue;
            }

            board[i][j].is_revealed = true;
        }
    }
}

void Game::RevealAdjacentCells(int row, int col)
{
    std::queue<std::pair<int, int>> q;
    q.push({row, col});

    while (!q.empty())
    {
        auto [current_row, current_col] = q.front();
        q.pop();

        struct Cell &cell = board[current_row][current_col];
        cell.is_revealed = true;

        for (const auto &direction : directions)
        {
            int new_row = current_row + direction[0];
            int new_col = current_col + direction[1];

            if (new_row < 0 || new_col < 0 || new_row >= rows || new_col >= cols)
            {
                continue;
            }

            struct Cell &new_cell = board[new_row][new_col];

            if (new_cell.is_revealed || new_cell.is_mine)
            {
                continue;
            }
            if (new_cell.adjacent_mines != 0)
            {
                continue;
            }

            q.push({new_row, new_col});
        }
    }
}

bool Game::CheckWinCondition()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!board[i][j].is_mine && !board[i][j].is_revealed)
            {
                return false;
            }
        }
    }

    return true;
}

std::pair<int, int> Game::GetRowAndCol()
{
    int row = -1, col = 0;

    while (row < 1 || row > rows)
    {
        std::cout << std::string(WHITE) + "Enter the row of the cell you want to reveal: ";
        std::cin >> row;

        if (row < 1 || row > rows)
        {
            std::cout << std::string(RED) + "Row must be from 1 to " + std::to_string(rows) + ".\n\n";
        }
    }
    while (col < 1 || col > cols)
    {
        std::cout << std::string(WHITE) + "Enter the column of the cell you want to reveal: ";
        std::cin >> col;

        if (col < 1 || col > cols)
        {
            std::cout << std::string(RED) + "Column must be from 1 to " + std::to_string(cols) + ".\n\n";
        }
    }

    // The user is expected to input 1-based indices, so we adjust them to 0-based indices for internal processing.
    row -= 1; // Adjust for 0-based index
    col -= 1; // Adjust for 0-based index

    return {row, col};
}